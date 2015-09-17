/*
 * Enemy.cpp
 *
 *  Created on: Nov 22, 2013
 *      Author: Armin Halilovic
 */

#include "Enemy.h"


namespace Entities {

/// Default constructor.
Enemy::Enemy() : Entity(), speed(0), points(0), movingLeft(true) { }

/// Parametrized constructor.
Enemy::Enemy(int x, int y, int width, int height, int points, int speed, bool movingLeft) :
		Entity(x, y, width, height), speed(speed), points(points), movingLeft(movingLeft) { }

/// Destructor.
Enemy::~Enemy() { }

/// Return the speed of the invader.
int Enemy::getSpeed() const {
	return speed;
}

/// Set the speed of the invader.
void Enemy::setSpeed(int speed) {
	this->speed = speed;
}

/// Return the points the invader is worth.
int Enemy::getPoints() const {
	return points;
}

/// set the points the invader is worth.
void Enemy::setPoints(int points) {
	this->points = points;
}

/// Return the direction of the invader.
bool Enemy::isMovingLeft() const {
	return movingLeft;
}

/// Set the direction of the invader.
void Enemy::setMovingLeft(bool movingLeft) {
	this->movingLeft = movingLeft;
}

/// Make the invader move (left or right).
void Enemy::move() {
	if (movingLeft)
		setPosition(getPositionX() - speed, getPositionY());
	else
		setPosition(getPositionX() + speed, getPositionY());
}

/// Make the invader move down.
void Enemy::moveDown() {
	setPosition(getPositionX(), getPositionY() + speed * 2);
}

/// Return a Bullet with a position, direction and speed.
std::shared_ptr<Bullet> Enemy::shoot() {
	return std::shared_ptr<Bullet> (new Bullet(getPositionX() + getWidth() / 2, getPositionY() + getHeight(), 2, 10, 7, false));
}


} /* namespace Entities */
