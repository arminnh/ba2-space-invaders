/*
 * Entity.cpp
 *
 *  Created on: Dec 17, 2013
 *      Author: Armin Halilovic
 */

#include "Entity.h"
#include "Bullet.h"

namespace Entities {

/// Default constructor.
Entity::Entity() : x(0), y(0), width(0), height(0) { }

/// Parametrized constructor.
Entity::Entity(int x, int y, int width, int height) :x(x), y(y), width(width), height(height) { }

///Destructor.
Entity::~Entity() { }

//Return the x value of the entity.
int Entity::getPositionX() const {
	return x;
}

//Return the y value of the entity.
int Entity::getPositionY() const {
	return y;
}

/// Set the x and y value of the entity.
void Entity::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

/// Return the width of the entity.
int Entity::getWidth() const {
	return width;
}

/// Return the height of the entity.
int Entity::getHeight() const {
	return height;
}

/// Set the width and height of the entity.
void Entity::setDimensions(int width, int height) {
	this->width = width;
	this->height = height;
}

/// Check whether or not the entity contains a Bullet.
bool Entity::contains(std::shared_ptr<Bullet> bullet) {
	// Look at Entity and Bullet as rectangles.
	// If they touch each other in any way, function will return 1.
	if ((x <= bullet->getPositionX() and bullet->getPositionX() <= x + width
			and y <= bullet->getPositionY() and bullet->getPositionY() <= y + height)
		or (x <= bullet->getPositionX() + bullet->getWidth() and bullet->getPositionX() + bullet->getWidth() <= x + width
			and y < bullet->getPositionY() and bullet->getPositionY() < y + height)
		or (x <= bullet->getPositionX() and bullet->getPositionX() <= x + width
			and y <= bullet->getPositionY() + bullet->getHeight() and bullet->getPositionY() + bullet->getHeight() <= y + height)
		or (x <= bullet->getPositionX() + bullet->getWidth() and bullet->getPositionX() + bullet->getWidth() <= x + width
			and y <= bullet->getPositionY() + bullet->getHeight() and bullet->getPositionY() + bullet->getHeight() <= y + height))
		return 1;

	return 0;
}

} /* namespace Entities */
