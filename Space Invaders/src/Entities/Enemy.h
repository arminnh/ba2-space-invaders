/*
 * Enemy.h
 *
 *  Created on: Nov 22, 2013
 *      Author: Armin Halilovic
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "Entity.h"
#include "Bullet.h"
#include <memory>

namespace Entities{

/**
 * Enemy class to represent the invaders.
 */
class Enemy : public Entity {
private:
	int speed, points;
	bool movingLeft;

public:
	/// Default constructor.
	Enemy();

	/// Parametrized constructor.
	Enemy(int, int, int, int, int, int, bool);

	/// Destructor.
	virtual ~Enemy();

	/// Return the speed of the invader.
	int getSpeed() const;
	/// Set the speed of the invader.
	void setSpeed(int);

	/// Return the points the invader is worth.
	int getPoints() const;
	/// set the points the invader is worth.
	void setPoints(int);

	/// Return the direction of the invader.
	bool isMovingLeft() const;
	/// Set the direction of the invader.
	void setMovingLeft(bool);

	/// Make the invader move (left or right).
	void move();
	/// Make the invader move down.
	void moveDown();

	/// Return a Bullet with a position, direction and speed.
	std::shared_ptr<Bullet> shoot();
};

} /* namespace Entities */

#endif /* ENEMY_H_ */
