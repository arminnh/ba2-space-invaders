/*
 * PowerUp.cpp
 *
 *  Created on: Nov 22, 2013
 *      Author: Armin Halilovic
 */

#include "PowerUp.h"

namespace Entities {

/// Default constructor.
PowerUp::PowerUp() : Entity(), type(0) { }

/// Parametrized constructor.
PowerUp::PowerUp(int x, int y, int width, int height, int type) : Entity(x, y, width, height), type(type) { }

/// Destructor.
PowerUp::~PowerUp() { }

/// Return the type of the power up.
int PowerUp::getType() const {
	return type;
}

/// Set the type of the power up.
void PowerUp::setType(int type) {
	this->type = type;
}

/// Check whether or not a cannon touches the power up.
bool PowerUp::contains(std::shared_ptr<Cannon> cannon) {
	// Look at PowerUp and Cannon as rectangles.
	// If they touch each other in any way, function will return 1.
	if ((getPositionX() <= cannon->getPositionX() and cannon->getPositionX() <= getPositionX() + getWidth()
			and getPositionY() <= cannon->getPositionY() and cannon->getPositionY() <= getPositionY() + getHeight())
		or (getPositionX() <= cannon->getPositionX() + cannon->getWidth() and cannon->getPositionX() + cannon->getWidth() <= getPositionX() + getWidth()
			and getPositionY() < cannon->getPositionY() and cannon->getPositionY() < getPositionY() + getHeight())
		or (getPositionX() <= cannon->getPositionX() and cannon->getPositionX() <= getPositionX() + getWidth()
			and getPositionY() <= cannon->getPositionY() + cannon->getHeight() and cannon->getPositionY() + cannon->getHeight() <= getPositionY() + getHeight())
		or (getPositionX() <= cannon->getPositionX() + cannon->getWidth() and cannon->getPositionX() + cannon->getWidth() <= getPositionX() + getWidth()
			and getPositionY() <= cannon->getPositionY() + cannon->getHeight() and cannon->getPositionY() + cannon->getHeight() <= getPositionY() + getHeight()))
		return 1;

	return 0;
}

} /* namespace Entities */
