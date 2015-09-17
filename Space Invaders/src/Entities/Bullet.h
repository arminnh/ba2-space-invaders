/*
 * Bullet.h
 *
 *  Created on: Nov 22, 2013
 *      Author: Armin Halilovic
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Entity.h"

namespace Entities {

/**
 * Represents a Bullet in the game.
 */
class Bullet : public Entity {
private:
	int speed;
	bool movingUp;

public:
	/// Default constructor.
	Bullet();

	/// Parametrized contructor.
	Bullet(int, int, int, int, int, bool);

	/// Destructor.
	~Bullet();

	/// Return the speed of the bullet.
	int getSpeed() const;
	/// Set the speed of the bullet.
	void setSpeed(int);

	/// Return the direction of the bullet.
	bool getMovingUp() const;
	/// Set the direction of the bullet.
	void setMovingUp(bool movingUp);

	/// Make the bullet move.
	void move();
};

} /* namespace Entities */

#endif /* BULLET_H_ */
