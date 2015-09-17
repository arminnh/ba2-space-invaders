/*
 * GameModel.h
 *
 *  Created on: Dec 4, 2013
 *      Author: Armin Halilovic
 */

#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include <vector>
#include <memory>
#include "GameView.h"
#include "../Entities/Enemy.h"
#include "../Entities/Cannon.h"
#include "../Entities/Bullet.h"
#include "../Entities/PowerUp.h"
#include "../Entities/Factories.h"
#include "../Entities/Wall.h"

namespace MVC {

/**
 * GameModel is the "Model" part of the MVC pattern used for the game.
 * GameModel contains all the game entities, game logic and some trivial integers.
 */
class GameModel {
private:
	bool enemiesMoveDown, gameOver;
	int score, lives, level, enemiesShot, powerUpType, powerUpTime;

	std::shared_ptr< Entities::EntityFactory> factory;

	std::shared_ptr< Entities::Enemy > ufo;
	std::shared_ptr< Entities::Cannon > player;
	std::shared_ptr< Entities::PowerUp > powerUp;
	std::shared_ptr< Entities::Bullet > playerBullet;

	std::vector<std::shared_ptr<Entities::Wall>> shields;
	std::vector<std::shared_ptr<Entities::Bullet>> enemyBullets;
	std::vector< std::vector<std::shared_ptr<Entities::Enemy>> > enemies;

	std::vector<std::shared_ptr<Observer>> observers;

public:
	/// Default constructor.
	GameModel();

	/// Destructor.
	~GameModel();

	/// Function to inizialize shields, used by the constructor.
	void initializeShields();
	/// Function to initialize entities, used by the constructor.
	void initializeEntities();

	/// Reset GameModel.
	void reset();

	/// Return the score.
	int getScore() const;
	/// Return the amount of lives.
	int getLives() const;
	/// Check whether or not the game is over.
	bool isGameOver() const;
	/// Return the power up type.
	int getPowerUpType() const;
	/// Return the amount of enemies that were shot.
	double getEnemiesShot() const;
	/// Return a pointer that represents the UFO.
	std::shared_ptr< Entities::Enemy > getUFO() const;
	/// Return a pointer that represents the power up.
	std::shared_ptr< Entities::PowerUp > getPowerup() const;
	/// Return a pointer that represents the player.
	std::shared_ptr< Entities::Cannon > getPlayer() const;
	/// Return a pointer that represents the player's bullet.
	std::shared_ptr< Entities::Bullet > getPlayerBullet() const;
	/// Return a vector of pointers to Wall objects, this represents a shield.
	std::vector< std::shared_ptr<Entities::Wall> > getShields() const;
	/// Return a vector of pointers to Bullets objects which represent the enemies' bullets.
	std::vector< std::shared_ptr<Entities::Bullet> > getEnemyBullets() const;
	/// Return a vector of vectors of pointers  to Enemy objects, this represents the grid of enemies.
	std::vector< std::vector<std::shared_ptr<Entities::Enemy>> > getEnemies() const;

	/// Make the cannon  move left and check if it got a power up.
	void movePlayerLeft();
	/// Make the cannon  move right and check if it got a power up.
	void movePlayerRight();

	/// Make the UFO move.
	void moveUFO();
	/// Spawn a new UFO.
	void spawnUFO();

	/// Make all the enemies move.
	void moveEnemies();
	/// Move all the enemies down.
	void moveEnemiesDown();
	/// Check wheter or not the enemies are near the sides of the window.
	bool enemiesNearWall() const;
	/// Check wheter or not the enemies are near the bottom of the window.
	bool enemiesNearBase() const;

	/// Make the cannon shoot.
	void playerShoot();
	/// Make the enemies shoot.
	void enemiesShoot();
	/// Move player's bullet and do the right actions if it hit something.
	void doPlayerBullet();
	/// Move enemies' bullets and do the right actions if they hit something.
	void doEnemyBullets();
	/// Use doPlayerBullet and doEnemyBullets.
	void checkAndMoveBullets();

	/// Make the cannon die.
	void die();
	/// Go to the next level.
	void nextLevel();
	/// Check whether or not the game is over or the level was completed.
	void checkLevel();

	/// Spawn a new power up.
	void spawnPowerUp();
	/// Tick the power up's timer.
	void tickPowerUp();

	/// Register a new observer.
	void registerObserver(std::shared_ptr<Observer>);
	/// Unregister a new observer.
	void unregisterObserver(std::shared_ptr<Observer>);

	/// Update the obsevers for a reset.
	void notifyObserversReset();
	/// Update the obsevers for everything.
	void notifyObserversAll();
	/// Update the obsevers for the UFO.
	void notifyObserversUFO();
	/// Update the obsevers for the text.
	void notifyObserversText();
	/// Update the obsevers for the player.
	void notifyObserversPlayer();
	/// Update the obsevers for the enemies.
	void notifyObserversEnemies();
	/// Update the obsevers for the bullets.
	void notifyObserversBullets();
	/// Update the obsevers for the shields.
	void notifyObserversShields();
	/// Update the obsevers for the power up.
	void notifyObserversPowerUp();
};

} /* namespace MVC */

#endif /* GAMEMODEL_H_ */
