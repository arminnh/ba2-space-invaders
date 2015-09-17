/*
 * Factories.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: Armin Halilovic
 */

#include <random>
#include <chrono>
#include <iostream>
#include "Factories.h"

std::default_random_engine generator((unsigned int)time(0));

namespace Entities {

Factory::~Factory() { }

/// Default constructor.
EntityFactory::EntityFactory() { }

/// Destructor.
EntityFactory::~EntityFactory() { }

/// Return a pointer to an Enemy object.
std::shared_ptr<Enemy> EntityFactory::createEnemy(int type){
	std::shared_ptr<Enemy> enemy (new Enemy);
	enemy->setSpeed(10);
	enemy->setDimensions(35, 35);
	enemy->setMovingLeft(false);

	switch(type) {
		case 1:
			enemy->setPoints(10);
			break;
		case 2:
			enemy->setPoints(20);
			break;
		case 3:
			enemy->setPoints(40);
			break;
		case 4: {
			std::uniform_int_distribution<int> distribution(1, 3);
			enemy->setSpeed(3);
			enemy->setDimensions(47, 21);

			switch(distribution(generator)) {
				case 1:
					enemy->setPoints(100);
					break;
				case 2:
					enemy->setPoints(250);
					break;
				case 3:
					enemy->setPoints(500);
					break;
			}
			break;
		}
		default:
			std::cout << "Enemy type not recognised, returned null." << std::endl;
			return nullptr;
	}

	return enemy;
}

/// Return a pointer to a Cannon object.
std::shared_ptr<Cannon> EntityFactory::createCannon(){
	return std::shared_ptr<Cannon> (new Cannon(0, 575, 43, 22, 6));
}

/// Return a pointer to a Wall object.
std::shared_ptr<Wall> EntityFactory::createWall(){
	return std::shared_ptr<Wall> (new Wall(0, 0, 20, 20, 3));
}

/// Return a pointer to a PowerUp object.
std::shared_ptr<PowerUp> EntityFactory::createPowerUp(int type){
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distribution(1, 780);
	return std::shared_ptr<PowerUp> (new PowerUp(distribution(generator), 575, 20, 27, type));
}

} /* namespace Entities */
