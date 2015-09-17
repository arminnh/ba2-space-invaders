/*
 * Wall.h
 *
 *  Created on: Dec 16, 2013
 *      Author: Armin Halilovic
 */

#ifndef WALL_H_
#define WALL_H_

#include "Entity.h"

namespace Entities {

/**
 * Represents a wall in the game to shield the cannon from bullets.
 */
class Wall : public Entity {
private:
	int hp;

public:
	/// Default constructor.
	Wall();

	/// Parametrized constructor.
	Wall(int, int, int, int, int);

	/// Parametrized destructor.
	~Wall();

	/// Return the health points of the wall.
	int getHP() const;
	/// Set the health points of the wall.
	void setHP(int);
};

} /* namespace Entities */

#endif /* WALL_H_ */
