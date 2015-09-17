/*
 * GameView.h
 *
 *  Created on: Dec 4, 2013
 *      Author: Armin Halilovic
 */

#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include <vector>
#include <memory>
#include "Observer.h"
#include "MySprite.h"
#include <SFML/Graphics.hpp>
#include "../Entities/Enemy.h"
#include "../Entities/Cannon.h"
#include "../Entities/Bullet.h"
#include "../Entities/PowerUp.h"
#include "../Entities/Wall.h"

namespace MVC {

// Forward declaration of GameModel to be used in GameView.
class GameModel;

/**
 * GameView is the "View" part of the MVC pattern used for the game.
 * GameView derives from Observer and will be GameModel's observer.
 * The class consists of a window, text and images (textures and sprites).
 */
class GameView : public Observer {
private:
	sf::RenderWindow window;

	sf::Font font;
	std::vector<sf::Text> text;

	sf::Texture spriteSheet;
	sf::Texture backgroundImage;
	sf::Texture pauseScreenImage;

	sf::Sprite background;
	sf::Sprite pauseScreen;

	sf::Sprite ufo;
	sf::Sprite player;
	sf::MySprite powerUp;
	sf::MySprite powerUp2;
	sf::Sprite playerBullet;

	std::vector <sf::Sprite> shields;
	std::vector <sf::Sprite> enemyBullets;
	std::vector < std::vector<std::shared_ptr<sf::MySprite>> > enemies;

public:
	/// Default constructor.
	GameView();

	///Destructor
	~GameView();

	/// Function to initialize the text, used in the constructor.
	void initializeText();
	/// Function to initialize the shields, used in the constructor.
	void initializeShields();
	/// Function to initialize the invaders, used in the constructor.
	void initializeEnemies();

	/// Reset GameView.
	void reset();

	/// Close the screen.
	void close();
	/// Check whether or not window is opened.
	bool isOpen();
	/// Check whether or not an event occured.
	bool pollEvent(sf::Event &event);

	/// Draw all images to the window.
	void draw();
	/// Draw the ending screen.
	void doEndScreen();
	/// Draw the intro screen.
	void doIntroScreen();
	/// Draw the pause screen.
	void doPauseScreen();

	/// Clear the window.
	void clear();
	/// Display the window.
	void display();

	/// Update for reset.
	void notifyReset();
	/// Update for UFO.
	void notifyUFO(GameModel*);
	/// Update for text.
	void notifyText(GameModel*);
	/// Update for player.
	void notifyPlayer(GameModel*);
	/// Update for power up.
	void notifyPowerUp(GameModel*);
	/// Update for enemies.
	void notifyEnemies(GameModel*);
	/// Update for bullets.
	void notifyBullets(GameModel*);
	/// Update for shields.
	void notifyShields(GameModel*);
};


} /* namespace MVC */

#endif /* GAMEVIEW_H_ */
