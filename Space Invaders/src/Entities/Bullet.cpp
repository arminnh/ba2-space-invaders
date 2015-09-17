/*
 * Bullet.cpp
 *
 *  Created on: Nov 22, 2013
 *      Author: Armin Halilovic
 */

#include "Bullet.h"

namespace Entities {

/// Default constructor.
Bullet::Bullet() : Entity(), speed(0), movingUp(false) { }

/// Parametrized contructor.
Bullet::Bullet(int x, int y, int width, int height, int speed, bool movingUp) :
						Entity(x, y, width, height), speed(speed), movingUp(movingUp) { }

/// Destructor.
Bullet::~Bullet() { }

/// Return the speed of the bullet.
int Bullet::getSpeed() const{
	return speed;
}

/// Set the speed of the bullet.
void Bullet::setSpeed(int speed) {
	this->speed = speed;
}

/// Return the direction of the bullet.
bool Bullet::getMovingUp() const {
	return movingUp;
}

/// Set the direction of the bullet.
void Bullet::setMovingUp(bool movingUp) {
	this->movingUp = movingUp;
}

/// Make the bullet move.
void Bullet::move() {
	if (movingUp) {
		setPosition(getPositionX(), getPositionY() - speed);
	} else {
		setPosition(getPositionX(), getPositionY() + speed);
	}
}


} /* namespace Entities */
