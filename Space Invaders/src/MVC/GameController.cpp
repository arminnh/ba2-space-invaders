/*
 * GameController.cpp
 *
 *  Created on: Dec 4, 2013
 *      Author: Armin Halilovic
 */

#include "GameController.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <chrono>

std::default_random_engine randomGenerator((unsigned int)time(0));

namespace MVC {

using namespace std;

/// Parametrized constructor.
GameController::GameController(std::shared_ptr<GameModel> gameModel, std::shared_ptr<GameView> gameView)
										: model(gameModel), view(gameView), paused(false), enemySpeed(0.55) { }

/// Destructor.
GameController::~GameController() { }

/// Handle all events.
void GameController::handleEvents() {
	sf::Event event;

	while(view->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			view->close();

		if (event.type == sf::Event::KeyReleased and
			(event.key.code == sf::Keyboard::Escape or event.key.code == sf::Keyboard::P)) {
			paused = !paused;
		}
	}
}

/// Handle the keyboard input. (Separated from handleEvents to optimize for live input.)
void GameController::handleKeyboard() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (model->getPlayer()->getPositionX() < 750)
			model->movePlayerRight();

	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (model->getPlayer()->getPositionX() > 0)
			model->movePlayerLeft();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		model->playerShoot();
	}

}

/// Start the game.
void GameController::game() {
	sf::Clock clock;

	while(view->isOpen()) {
		handleEvents();

		if (!model->isGameOver()) {
			if (!paused) {
				handleKeyboard();

				// Move the enemies in certain time intervals
				// If power up type is 2, dont move the enemies. Power up type 2 freezes the enemies.
				if (clock.getElapsedTime().asSeconds() > enemySpeed and model->getPowerUpType() != 2) {
					model->moveEnemies();
					clock.restart();
				}

				// If there is no UFO and there are a minimum of 16 invaders, a UFO might spawn.
				if (model->getUFO() == nullptr) {
					std::uniform_int_distribution<int> distribution(1, 600);
					if (model->getEnemiesShot() < 40 and distribution(randomGenerator) == 1)
						model->spawnUFO();
				} else {
					model->moveUFO();
				}

				// Make random enemies shoot with a random chance.
				model->enemiesShoot();

				// If there are bullets, move them and handle accordingly for casualties.
				if (model->getPlayerBullet() != nullptr or !model->getEnemyBullets().empty())
					model->checkAndMoveBullets();

				// If there is no power up on the field, make a new one spawn by chance.
				if (model->getPowerup() == nullptr and model->getPowerUpType() == 0) {
					std::uniform_int_distribution<int> distribution(1, 500);
					if (distribution(randomGenerator) == 1)
						model->spawnPowerUp();
				} else {
					model->tickPowerUp();
				}

				// Adjust the time interval in which the enemies will move.
				enemySpeed = pow(0.96, model->getEnemiesShot()) * 0.55;

				// Check whether or not the level should end.
				model->checkLevel();

				view->draw();
				view->display();
				view->clear();
			} else {
				view->doPauseScreen();
			}

		} else {
			view->doEndScreen();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				restart();
		}
	}
}

/// Start the intro for the game.
void GameController::intro() {
	bool intro = true;

	while(intro and view->isOpen()) {
		sf::Event event;

		while(view->pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed:
				view->close();
				break;
			case sf::Event::KeyPressed:
				intro = false;
				break;
			}
		}
		view->doIntroScreen();
	}
}

/// Restart the game.
void GameController::restart() {
	model->reset();
	view->reset();
	paused = false;
	enemySpeed = 0.55;

	model->notifyObserversAll();
}

} /* namespace MVC */
