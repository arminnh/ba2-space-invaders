/*
 * Wall.cpp
 *
 *  Created on: Dec 16, 2013
 *      Author: Armin Halilovic
 */

#include "Wall.h"

namespace Entities {

/// Default constructor.
Wall::Wall() : Entity(), hp(0) { }

/// Parametrized constructor.
Wall::Wall(int x, int y, int width, int height, int hp) : Entity(x, y, width, height), hp(hp) { }

/// Parametrized destructor.
Wall::~Wall() { }

/// Return the health points of the wall.
int Wall::getHP() const {
	return hp;
}

/// Set the health points of the wall.
void Wall::setHP(int hp) {
	this->hp = hp;
}

} /* namespace Entities */
