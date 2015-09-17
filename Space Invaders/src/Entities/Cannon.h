/*
 * CANNON.h
 *
 *  Created on: Nov 22, 2013
 *      Author: Armin Halilovic
 */

#ifndef CANNON_H_
#define CANNON_H_

#include "Entity.h"
#include "Bullet.h"
#include <memory>

namespace Entities {

/**
 * Cannon that can shoot the invaders.
 */
class Cannon : public Entity {
private:
	int speed;
public:
	/// Default constructor.
	Cannon();

	/// Parametrized constructor.
	Cannon(int, int, int, int, int);

	/// Destructor.
	~Cannon();

	/// Return the speed of the cannon.
	int getSpeed();
	/// Set the speed of the cannon.
	void setSpeed(int);

	/// Make the cannon move left for an amount depending on its speed.
	void moveLeft();
	/// Make the cannon move right for an amount depending on its speed.
	void moveRight();

	/// Return a bullet with a position, direction and speed.
	std::shared_ptr<Bullet> shoot() const;
};

} /* namespace Entities */

#endif /* CANNON_H_ */
