/*
 * Cannon.cpp
 *
 *  Created on: Nov 22, 2013
 *      Author: Armin Halilovic
 */

#include "Cannon.h"

namespace Entities {

/// Default constructor.
Cannon::Cannon() : Entity(), speed(0) { }

/// Parametrized constructor.
Cannon::Cannon(int x, int y, int width, int height, int speed) : Entity(x, y, width, height), speed(speed) { }

/// Destructor.
Cannon::~Cannon() {}

/// Return the speed of the cannon.
int Cannon::getSpeed() {
	return speed;
}

/// Set the speed of the cannon.
void Cannon::setSpeed(int speed) {
	this->speed = speed;
}

/// Make the cannon move left for an amount depending on its speed.
void Cannon::moveLeft() {
	setPosition(getPositionX() - speed, getPositionY());
}

/// Make the cannon move right for an amount depending on its speed.
void Cannon::moveRight() {
	setPosition(getPositionX() + speed, getPositionY());
}

/// Return a bullet with a position, direction and speed.
std::shared_ptr<Bullet> Cannon::shoot() const {
	return std::shared_ptr<Bullet> (new Bullet(getPositionX() + (getWidth() / 2), getPositionY(), 2, 10, 9, true));
}

} /* namespace Entities */
