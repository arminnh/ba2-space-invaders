/*
 * GameView.cpp
 *
 *  Created on: Dec 4, 2013
 *      Author: Armin Halilovic
 */

#include <chrono>
#include <thread>
#include <exception>
#include "GameView.h"
#include "GameModel.h"
#include "MyException.h"
#include "../Entities/Factories.h"

#include <iostream>

namespace MVC {

/// Default constructor.
GameView::GameView() {
	window.create(sf::VideoMode(800, 600), "Space Invaders");
	window.setFramerateLimit(60);

	if(!spriteSheet.loadFromFile("../images/spriteSheet.png"))
		throw MyException("Could not load spriteSheet");
	if(!backgroundImage.loadFromFile("../images/background.png"))
		throw MyException("Could not load backgroundImage");
	if(!pauseScreenImage.loadFromFile("../images/pauseScreen.png"))
		throw MyException("Could not load pauseScreenImage");

	background.setTexture(backgroundImage);
	pauseScreen.setTexture(pauseScreenImage);

	ufo.setTexture(spriteSheet);
	player.setTexture(spriteSheet);
	powerUp.setTexture(spriteSheet);
	powerUp2.setTexture(spriteSheet);
	playerBullet.setTexture(spriteSheet);
	ufo.setTextureRect(sf::IntRect(80, 40, 50, 21));
	player.setTextureRect(sf::IntRect(80, 0, 46, 22));
	powerUp.setTextureRect(sf::IntRect(131, 0, 20, 20));
	powerUp2.setTextureRect(sf::IntRect(131, 0, 20, 20));
	playerBullet.setTextureRect(sf::IntRect(131, 0, 2, 10));

	initializeText();
	initializeShields();
	initializeEnemies();
}

///Destructor
GameView::~GameView() {
	if (window.isOpen())
		window.close();
}

/// Function to initialize the text, used in the constructor.
void GameView::initializeText() {
	if(!font.loadFromFile("../images/PressStart2P.ttf"))
		throw MyException("Could not load font");

	text = std::vector<sf::Text>(4);

	text[0] = sf::Text("SCORE", font, 21);
	text[0].setPosition(10, 10);
	text[0].setColor(sf::Color(255, 255, 255));

	text[1] = sf::Text("", font, 21); // Score, empty at start.
	text[1].setPosition(130, 10);
	text[1].setColor(sf::Color(0, 252, 0));

	text[2] = sf::Text("LIVES", font, 21);
	text[2].setPosition(610, 10);
	text[2].setColor(sf::Color(255, 255, 255));

	text[3] = sf::Text("", font, 21); // Lives, empty at start.
	text[3].setPosition(730, 10);
	text[3].setColor(sf::Color(0, 252, 0));
}

/// Function to initialize the shields, used in the constructor.
void GameView::initializeShields() {
	shields.clear();

	// The difference between full_block and block is visible in the spritesheet image.
	sf::Sprite full_block(spriteSheet, sf::IntRect(131, 0, 20, 20));
	sf::Sprite block(spriteSheet);

	for (int i = 0; i < 4;  i++) {
		block.setTextureRect(sf::IntRect(131, 20, 20, 20));
		block.setPosition((96 + i * (80  + 96)), 480);
		shields.push_back(block);

		full_block.setPosition((116 + i * (80  + 96)), 480);
		shields.push_back(full_block);

		full_block.setPosition((136 + i * (80  + 96)), 480);
		shields.push_back(full_block);

		block.setTextureRect(sf::IntRect(131, 40, 20, 20));
		block.setPosition((156 + i * (80  + 96)), 480);
		shields.push_back(block);

		full_block.setPosition((96 + i * (80  + 96)), 500);
		shields.push_back(full_block);

		block.setTextureRect(sf::IntRect(131, 60, 20, 20));
		block.setPosition((116 + i * (80  + 96)), 500);
		shields.push_back(block);

		block.setTextureRect(sf::IntRect(131, 80, 20, 20));
		block.setPosition((136 + i * (80  + 96)), 500);
		shields.push_back(block);

		full_block.setPosition((156 + i * (80  + 96)), 500);
		shields.push_back(full_block);

		full_block.setPosition((96 + i * (80  + 96)), 520);
		shields.push_back(full_block);

		full_block.setPosition((156 + i * (80  + 96)), 520);
		shields.push_back(full_block);;
	}
}

/// Function to initialize the invaders, used in the constructor.
void GameView::initializeEnemies() {
	enemies = std::vector< std::vector<std::shared_ptr<sf::MySprite>> >();
	for (int j = 0; j < 11; j++) {
		std::vector< std::shared_ptr<sf::MySprite> > column;
		std::shared_ptr<sf::MySprite> sprite;

		sprite = std::shared_ptr<sf::MySprite> (new sf::MySprite);
		sprite->setTexture(spriteSheet);
		sprite->setTextureRect(sf::IntRect(0, 80, 40, 40));
		column.push_back(sprite);

		sprite = std::shared_ptr<sf::MySprite> (new sf::MySprite);
		sprite->setTexture(spriteSheet);
		sprite->setTextureRect(sf::IntRect(0, 40, 40, 40));
		column.push_back(sprite);

		sprite = std::shared_ptr<sf::MySprite> (new sf::MySprite);
		sprite->setTexture(spriteSheet);
		sprite->setTextureRect(sf::IntRect(0, 40, 40, 40));
		column.push_back(sprite);

		sprite = std::shared_ptr<sf::MySprite> (new sf::MySprite);
		sprite->setTexture(spriteSheet);
		sprite->setTextureRect(sf::IntRect(0, 0, 40, 40));
		column.push_back(sprite);

		sprite = std::shared_ptr<sf::MySprite> (new sf::MySprite);
		sprite->setTexture(spriteSheet);
		sprite->setTextureRect(sf::IntRect(0, 0, 40, 40));
		column.push_back(sprite);

		enemies.push_back(column);
	}
}

/// Reset GameView.
void GameView::reset() {
	initializeText();
	initializeShields();
	initializeEnemies();
}

/// Close the screen.
void GameView::close() {
	window.close();
}

/// Check whether or not window is opened.
bool GameView::isOpen() {
	return window.isOpen();
}

/// Check whether or not an event occured.
bool GameView::pollEvent(sf::Event &event) {
	return window.pollEvent(event);
}

/// Draw all images to the window.
void GameView::draw() {
	window.draw(background);

	window.draw(playerBullet);
	for (auto it : enemyBullets)
		window.draw(it);
	for (auto it : shields)
		window.draw(it);

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 5; j++) {
			if (enemies[i][j] != nullptr)
				window.draw(*enemies[i][j]);
		}
	}

	window.draw(ufo);
	window.draw(player);
	window.draw(powerUp);
	window.draw(powerUp2);
	for (auto it : text)
		window.draw(it);
}

/// Draw the ending screen.
void GameView::doEndScreen() {
	sf::Text gameOver("GAME OVER", font, 35);
	sf::Text anyKey("PRESS ENTER TO RESTART", font, 20);
	gameOver.setPosition(240, 230);
	anyKey.setPosition(175, 580);

	draw();
	window.draw(pauseScreen);
	window.draw(gameOver);
	window.draw(anyKey);
	display();
	clear();
}

/// Draw the intro screen.
void GameView::doIntroScreen() {
	sf::Text space("SPACE", font, 40);
	sf::Text invaders("INVADERS", font, 40);
	sf::Text type1("= 10 PTS", font, 25);
	sf::Text type2("= 20 PTS", font, 25);
	sf::Text type3("= 40 PTS", font, 25);
	sf::Text type4("= ?? PTS", font, 25);
	sf::Text anyKey("PRESS ANY KEY TO BEGIN", font, 20);
	space.setPosition(300, 75);
	invaders.setPosition(240, 115);
	type1.setPosition(345, 211);
	type2.setPosition(345, 265);
	type3.setPosition(345, 315);
	type4.setPosition(345, 365);
	anyKey.setPosition(175, 580);

	sf::Sprite type11(spriteSheet, sf::IntRect(0, 0, 40, 40));
	sf::Sprite type22(spriteSheet, sf::IntRect(0, 40, 40, 40));
	sf::Sprite type33(spriteSheet, sf::IntRect(0, 80, 40, 40));
	sf::Sprite type44(spriteSheet, sf::IntRect(80, 40, 50, 21));

	type11.setScale(1.3, 1.3);
	type22.setScale(1.3, 1.3);
	type33.setScale(1.3, 1.3);
	type44.setScale(1.3, 1.3);
	type11.setPosition(265, 200);
	type22.setPosition(263, 250);
	type33.setPosition(262, 300);
	type44.setPosition(256, 360);

	window.draw(background);
	window.draw(space);
	window.draw(invaders);
	window.draw(anyKey);
	window.draw(type1);
	window.draw(type2);
	window.draw(type3);
	window.draw(type4);
	window.draw(type11);
	window.draw(type22);
	window.draw(type33);
	window.draw(type44);
	window.display();
	window.clear();
}

/// Draw the pause screen.
void GameView::doPauseScreen() {
	sf::Text pause("PAUSED", font, 30);
	pause.setPosition(310, 280);

	draw();
	window.draw(pauseScreen);
	window.draw(pause);
	display();
	clear();
	std::this_thread::sleep_for(std::chrono::milliseconds(80));

	draw();
	window.draw(pauseScreen);
	display();
	clear();
	std::this_thread::sleep_for(std::chrono::milliseconds(80));
}

/// Clear the window.
void GameView::clear() {
	window.clear();
}

/// Display the window.
void GameView::display() {
	window.display();
}

/// Update for reset.
void GameView::notifyReset() {
	initializeEnemies();
}

/// Update for UFO.
void GameView::notifyUFO(GameModel* model) {
	if (model->getUFO() != nullptr) {
		ufo.setPosition(model->getUFO()->getPositionX(), model->getUFO()->getPositionY());
	} if (model->getUFO() == nullptr) {
		ufo.setPosition(800, 600);
	}
}

/// Update for text.
void GameView::notifyText(GameModel* model) {
	text[1].setString(std::to_string(model->getScore()));
	text[3].setString(std::to_string(model->getLives()));
}

/// Update for player.
void GameView::notifyPlayer(GameModel* model) {
	player.setPosition(model->getPlayer()->getPositionX(), model->getPlayer()->getPositionY());
}

/// Update for power up.
void GameView::notifyPowerUp(GameModel* model) {
	if (model->getPowerup() == nullptr) {
		powerUp.setPosition(800, 600);
	} else {
		powerUp.setTextureRect(sf::IntRect(111 + model->getPowerup()->getType() * 20, 100, 20, 20));
		powerUp.setPosition(model->getPowerup()->getPositionX(), model->getPowerup()->getPositionY());
	}

	if (model->getPowerUpType() != 0) {
		powerUp2.setTextureRect(sf::IntRect(111 + model->getPowerUpType() * 20, 100, 20, 20));
		powerUp2.setPosition(500, 10);
	} else {
		powerUp2.setPosition(800, 600);
	}
}

/// Update for enemies.
void GameView::notifyEnemies(GameModel* model) {
	std::vector< std::vector<std::shared_ptr<Entities::Enemy>> > a = model->getEnemies();

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 5; j++) {
			if (a[i][j] != nullptr) {
				if (enemies[i][j] != nullptr) {
					enemies[i][j]->setPosition(a[i][j]->getPositionX(), a[i][j]->getPositionY());
					if (enemies[i][j]->getAnimation() == 0) {
						enemies[i][j]->setTextureRect(sf::IntRect(40, enemies[i][j]->getTextureRect().top, 40, 40));
						enemies[i][j]->setAnimation(1);
					} else {
						enemies[i][j]->setTextureRect(sf::IntRect(0, enemies[i][j]->getTextureRect().top, 40, 40));
						enemies[i][j]->setAnimation(0);
					}
				}
			} else {
				enemies[i][j] = nullptr;
			}
		}
	}
}

/// Update for bullets.
void GameView::notifyBullets(GameModel* model) {
	if (model->getPlayerBullet() != nullptr) {
		playerBullet.setPosition(model->getPlayerBullet()->getPositionX(), model->getPlayerBullet()->getPositionY());
	} else {
		playerBullet.setPosition(-10, 0);
	}

	if (enemyBullets.size() != model->getEnemyBullets().size()) {
		sf::Sprite bullet(spriteSheet, sf::IntRect(5, 10, 2, 10));
		while (enemyBullets.size() < model->getEnemyBullets().size()) {
			enemyBullets.push_back(bullet);
		}

		while (enemyBullets.size() > model->getEnemyBullets().size()) {
			enemyBullets.erase(enemyBullets.end());
		}
	}

	std::vector< std::shared_ptr<Entities::Bullet> > bullets = model->getEnemyBullets();
	for(unsigned int i = 0; i < bullets.size(); i++) {
		enemyBullets[i].setPosition(bullets[i]->getPositionX(), bullets[i]->getPositionY());
	}
}

/// Update for shields.
void GameView::notifyShields(GameModel* model) {
	std::vector<std::shared_ptr<Entities::Wall>> a = model->getShields();

	for (unsigned int i = 0; i < shields.size(); i++) {
		shields[i].setTextureRect(sf::IntRect(
				131 + (20 * (3 - a[i]->getHP())),
				shields[i].getTextureRect().top,
				20,
				20));
	}
}

} /* namespace MVC */
