/*
 * GameModel.cpp
 *
 *  Created on: Dec 4, 2013
 *      Author: Armin Halilovic
 */

#include "GameModel.h"
#include <iostream>
#include <random>
#include <chrono>
#include <thread>

std::default_random_engine engine((unsigned int)time(0));

namespace MVC {

/// Default constructor.
GameModel::GameModel() : enemiesMoveDown(false), gameOver(false),
							score(0), lives(3), level(0), enemiesShot(0), powerUpType(0), powerUpTime(0) {
	factory = std::shared_ptr< Entities::EntityFactory > (new Entities::EntityFactory);
	initializeShields();
	initializeEntities();
}

/// Destructor.
GameModel::~GameModel() { }

/// Function to inizialize shields, used by the constructor.
void GameModel::initializeShields() {
	shields.clear();

	std::shared_ptr<Entities::Wall> block;
	for (int shield = 0; shield < 4; shield++) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				if (i == 2 and (j == 1 or j == 2)) {
					// Dont make a Wall for the middle two blocks in the bottom row.
				} else {
					block = factory->createWall();
					block->setPosition((96 + (20 * j) + shield * (80  + 96)), 480 + (20 * i));
					shields.push_back(block);
				}
			}
		}
	}
}

/// Function to initialize entities, used by the constructor.
void GameModel::initializeEntities() {
	player = factory->createCannon();

	powerUpType = 0;
	powerUpTime = 0;

	ufo = nullptr;
	powerUp = nullptr;
	playerBullet = nullptr;

	enemies.clear();
	enemyBullets.clear();

	for (int j = 0; j < 11; j++) {
		std::vector< std::shared_ptr<Entities::Enemy> > enems;
		std::shared_ptr<Entities::Enemy> enemy = nullptr;

		enemy = factory->createEnemy(3);
		enemy->setPosition(50 + (j * 50), 90 + (level * 25));
		enems.push_back(enemy);

		enemy = factory->createEnemy(2);
		enemy->setPosition(50 + (j * 50), 130 + (level * 25));
		enems.push_back(enemy);

		enemy = factory->createEnemy(2);
		enemy->setPosition(50 + (j * 50), 170 + (level * 25));
		enems.push_back(enemy);

		enemy = factory->createEnemy(1);
		enemy->setPosition(50 + (j * 50), 210 + (level * 25));
		enems.push_back(enemy);

		enemy = factory->createEnemy(1);
		enemy->setPosition(50 + (j * 50), 250 + (level * 25));
		enems.push_back(enemy);

		enemies.push_back(enems);
	}
}

/// Reset GameModel.
void GameModel::reset() {
	score = 0;
	lives = 3;
	level = 0;
	enemiesShot = 0;
	gameOver = false;
	enemiesMoveDown = false;

	initializeShields();
	initializeEntities();
 }

/// Return the score.
int GameModel::getScore() const {
	return score;
}

/// Return the amount of lives.
int GameModel::getLives() const {
	return lives;
}

/// Check whether or not the game is over.
bool GameModel::isGameOver() const {
	return gameOver;
}

/// Return the power up type.
int GameModel::getPowerUpType() const {
	return powerUpType;
}

/// Return the amount of enemies that were shot.
double GameModel::getEnemiesShot() const {
	return enemiesShot;
}

/// Return a pointer that represents the UFO.
std::shared_ptr< Entities::Enemy > GameModel::getUFO() const {
	return ufo;
}

/// Return a pointer that represents the power up.
std::shared_ptr<Entities::PowerUp> GameModel::getPowerup() const {
	return powerUp;
}

/// Return a pointer that represents the player.
std::shared_ptr< Entities::Cannon > GameModel::getPlayer() const {
	return player;
}

/// Return a pointer that represents the player's bullet.
std::shared_ptr< Entities::Bullet > GameModel::getPlayerBullet() const {
	return playerBullet;
}

/// Return a vector of pointers to Wall objects, this represents a shield.
std::vector<std::shared_ptr<Entities::Wall>> GameModel::getShields() const {
	return shields;
}

/// Return a vector of pointers to Bullets objects which represent the enemies' bullets.
std::vector<std::shared_ptr<Entities::Bullet>> GameModel::getEnemyBullets() const {
	return enemyBullets;
}

/// Return a vector of vectors of pointers  to Enemy objects, this represents the grid of enemies.
std::vector< std::vector<std::shared_ptr<Entities::Enemy>> > GameModel::getEnemies() const {
	return enemies;
}

/// Make the cannon move left and check if it got a power up.
void GameModel::movePlayerLeft() {
	player->moveLeft();

	if (powerUp != nullptr and powerUp->contains(player)) {
		powerUpType = powerUp->getType();
		powerUp = nullptr;
		notifyObserversPowerUp();
	}

	notifyObserversPlayer();
}

/// Make the cannon move right and check if it got a power up.
void GameModel::movePlayerRight() {
	player->moveRight();

	if (powerUp != nullptr and powerUp->contains(player)) {
		powerUpType = powerUp->getType();
		powerUp = nullptr;
		notifyObserversPowerUp();
	}

	notifyObserversPlayer();
}

/// Make the UFO move.
void GameModel::moveUFO() {
	if (ufo != nullptr) {
		ufo->move();

		if (ufo->getPositionX() < -55 or ufo->getPositionX() > 860 )
			ufo = nullptr;
	}
	notifyObserversUFO();
}

/// Spawn a new UFO.
void GameModel::spawnUFO() {
	std::uniform_int_distribution<int> distribution(1,2);
	ufo = factory->createEnemy(4);

	if (distribution(engine) == 2) {
		ufo->setPosition(-50, 50);
		ufo->setMovingLeft(0);
	} else {
		ufo->setPosition(850, 50);
		ufo->setMovingLeft(1);
	}
	notifyObserversUFO();
}

/// Make all the enemies move.
void GameModel::moveEnemies() {
	if (enemiesNearWall() and !enemiesMoveDown) {
		moveEnemiesDown();
		enemiesMoveDown = true;
	} else {
		enemiesMoveDown = false;
		for (unsigned int i = 0; i < enemies.size(); i++) {
			for (unsigned int j = 0; j < enemies[i].size(); j++) {
				if 	(enemies[i][j] != nullptr)
					enemies[i][j]->move();
			}
		}
	}
	notifyObserversEnemies();
}

/// Move all the enemies down.
void GameModel::moveEnemiesDown() {
	for (unsigned int i = 0; i < enemies.size(); i++) {
		for (unsigned int j = 0; j < enemies[i].size(); j++) {
			if (enemies[i][j] != nullptr) {
				enemies[i][j]->moveDown();
				enemies[i][j]->setMovingLeft(!enemies[i][j]->isMovingLeft());
			}
		}
	}
}

/// Check wheter or not the enemies are near the sides of the window.
bool GameModel::enemiesNearWall() const {
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		for (auto it2 = it->begin(); it2 != it->end(); it2++) {
			if ((*it2) != nullptr) {
				if ((*it2)->getPositionX() <= 0 or (*it2)->getPositionX() >= 760) {
					return 1;
				}
			}
		}
	}
	return 0;
}

/// Check wheter or not the enemies are near the bottom of the window.
bool GameModel::enemiesNearBase() const {
	for (unsigned int i = 0; i < enemies.size(); i++) {
		for (int j = enemies[i].size() - 1; j >= 0; j--) {
			if (enemies[i][j] != nullptr and enemies[i][j]->getPositionY() >= 545) {
				return true;
			}
		}
	}

	return false;
}

/// Make the cannon shoot.
void GameModel::playerShoot() {
	if (playerBullet == nullptr) {
		playerBullet = player->shoot();
	}

	notifyObserversBullets();
}

/// Make the enemies shoot.
void GameModel::enemiesShoot() {
	std::uniform_int_distribution<int> distribution(1,350);

	for (unsigned int i = 0; i < enemies.size(); i++) {
		bool first = false;
		for (int j = enemies[i].size() - 1; j >= 0; j--) {
			if (enemies[i][j] != nullptr) {
				if (first == false and 5 == distribution(engine)) {
					enemyBullets.push_back(enemies[i][j]->shoot());
				}
				first = true;
			}
		}
	}

	notifyObserversBullets();
}

/// Move player's bullet and do the right actions if it hit something.
void GameModel::doPlayerBullet() {
	if (playerBullet != nullptr) {
		// Move the bullet
		playerBullet->move();

		// If type of power up = 3, move the bullet again.
		// Power up type 3 makes the cannon shoot faster.
		if (powerUpType == 3)
			playerBullet->move();

		// Remove the bullet if it has moved too far.
		if(playerBullet->getPositionY() < 40)
			playerBullet = nullptr;
	}

	// Check if the bullet hit the UFO.
	if (playerBullet != nullptr and ufo != nullptr) {
		if (ufo->contains(playerBullet)) {
			score += ufo->getPoints();
			ufo = nullptr;
			playerBullet = nullptr;
			notifyObserversUFO();
			notifyObserversText();
		}
	}

	// Check if the bullet hit an enemy.
	if (playerBullet != nullptr) {
		for (unsigned int i = 0; i < enemies.size(); i++) {
			for (int j = enemies[i].size() - 1; j >= 0; j--) {
				if (enemies[i][j] != nullptr and playerBullet != nullptr and enemies[i][j]->contains(playerBullet)) {
						score += enemies[i][j]->getPoints();
						enemiesShot++;
						playerBullet = nullptr;
						enemies[i][j] = nullptr;
						notifyObserversText();
				}
			}
		}
		// Notify twice so the animation count of the enemies stays the same (animation = 0 -> 1 -> 0).
		notifyObserversEnemies();
		notifyObserversEnemies();
	}


	// Check if the bullet hit a Wall.
	for (auto it : shields) {
		if (playerBullet != nullptr and it->getHP() > 0 and it->contains(playerBullet)) {
			it->setHP(it->getHP() - 1);
			playerBullet = nullptr;
			notifyObserversShields();
		}
	}
}

/// Move enemies' bullets and do the right actions if they hit something.
void GameModel::doEnemyBullets() {
	// Use a new vector for Bullets.
	std::vector<std::shared_ptr<Entities::Bullet>> a;

	for (auto it : enemyBullets) {
		// Move the bullet
		it->move();

		// Check if the bullet hit a shield.
		for (auto it2 : shields) {
			if (it != nullptr and it2->getHP() > 0 and it2->contains(it)) {
				it = nullptr;
				it2->setHP(it2->getHP() - 1);
				notifyObserversShields();
			}
		}

		// Check if the bullet hit the player.
		if (it != nullptr and player->contains(it)) {
			die();
			it = nullptr;
		}

		// Copy the bullet to the new vector, if it still is in the window.
		if (it != nullptr and it->getPositionY() < 600)
			a.push_back(it);
	}
	// New vector represents current bullets.
	enemyBullets = a;
}

/// Use doPlayerBullet and doEnemyBullets.
void GameModel::checkAndMoveBullets() {
	doPlayerBullet();
	doEnemyBullets();
	notifyObserversBullets();
}

/// Make the cannon die.
void GameModel::die() {
	lives--;
	if (lives > 0) {
		player->setPosition(0, 575);
		notifyObserversPlayer();
	}
	// Pause for a second so the player sees what happened.
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	notifyObserversText();
}

/// Go to the next level.
void GameModel::nextLevel() {
	if (level < 5)
		level++;
	else
		level = 5;

	lives++;
	score += 1000;
	enemiesShot = 0;

	initializeEntities();
	notifyObserversReset();
	notifyObserversAll();
}

/// Check whether or not the game is over or the level was completed.
void GameModel::checkLevel() {
	if (enemiesNearBase() or lives == 0) {
		gameOver = true;
	}

	if (enemiesShot == 55) {
		nextLevel();
	}
}

/// Spawn a new power up.
void GameModel::spawnPowerUp() {
	std::uniform_int_distribution<int> distribution(1,3);
	powerUp = factory->createPowerUp(distribution(engine));
	notifyObserversPowerUp();
}

/// Tick the power up's timer.
void GameModel::tickPowerUp() {
	// Increment the timer for power up type 2 and 3.
	if (powerUpType == 2 or powerUpType == 3)
		powerUpTime++;

	// For type 1, add a life.
	if (powerUpType == 1) {
		lives++;
		powerUpType = 0;
		notifyObserversText();
	}

	// After 10 seconds (600 ticks), reset the power up.
	if (powerUpTime == 600) {
		powerUpType = 0;
		powerUpTime = 0;
	}

	notifyObserversPowerUp();
}

/// Register a new observer.
void GameModel::registerObserver(std::shared_ptr<Observer> observer) {
	observers.push_back(observer);
}

/// Unregister a new observer.
void GameModel::unregisterObserver(std::shared_ptr<Observer> observer) {
	std::remove(observers.begin(), observers.end(), observer);
}

/// Update the obsevers for a reset.
void GameModel::notifyObserversReset() {
	for (auto it : observers) {
		it->notifyReset();
	}
}

/// Update the obsevers for everything.
void GameModel::notifyObserversAll() {
	for (auto it : observers) {
		it->notifyUFO(this);
		it->notifyText(this);
		it->notifyPlayer(this);
		it->notifyBullets(this);
		it->notifyEnemies(this);
		it->notifyShields(this);
		it->notifyPowerUp(this);
	}
}

/// Update the obsevers for the UFO.
void GameModel::notifyObserversUFO() {
	for (auto it : observers) {
		it->notifyUFO(this);
	}
}

/// Update the obsevers for the text.
void GameModel::notifyObserversText() {
	for (auto it : observers) {
		it->notifyText(this);
	}
}

/// Update the obsevers for the player.
void GameModel::notifyObserversPlayer() {
	for (auto it : observers) {
		it->notifyPlayer(this);
	}
}

/// Update the obsevers for the enemies.
void GameModel::notifyObserversEnemies() {
	for (auto it : observers) {
		it->notifyEnemies(this);
	}
}

/// Update the obsevers for the bullets.
void GameModel::notifyObserversBullets() {
	for (auto it : observers) {
		it->notifyBullets(this);
	}
}

/// Update the obsevers for the shields.
void GameModel::notifyObserversShields() {
	for (auto it : observers) {
		it->notifyShields(this);
	}
}

/// Update the obsevers for the power up.
void GameModel::notifyObserversPowerUp() {
	for (auto it : observers) {
		it->notifyPowerUp(this);
	}
}


} /* namespace MVC */
