/*
 * Factories.h
 *
 *  Created on: Nov 29, 2013
 *      Author: Armin Halilovic
 */

#ifndef FACTORIES_H_
#define FACTORIES_H_

#include <memory>
#include "Wall.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Cannon.h"
#include "PowerUp.h"

namespace Entities {

/**
 * Factory interface.
 */
class Factory {
public:
	virtual ~Factory();

	virtual std::shared_ptr<Enemy> createEnemy(int) = 0;
	virtual std::shared_ptr<Cannon> createCannon() = 0;
	virtual std::shared_ptr<Wall> createWall() = 0;
	virtual std::shared_ptr<PowerUp> createPowerUp(int) = 0;
};

/**
 * Entitiy factory to easily create objects.
 */
class EntityFactory : public Factory {
public:
	/// Default constructor.
	EntityFactory();

	/// Destructor.
	~EntityFactory();

	/// Return a pointer to an Enemy object.
	std::shared_ptr<Enemy> createEnemy(int);

	/// Return a pointer to a Cannon object.
	std::shared_ptr<Cannon> createCannon();

	/// Return a pointer to a Wall object.
	std::shared_ptr<Wall> createWall();

	/// Return a pointer to a PowerUp object.
	std::shared_ptr<PowerUp> createPowerUp(int);
};

} /* namespace Entities */

#endif /* FACTORIES_H_ */
