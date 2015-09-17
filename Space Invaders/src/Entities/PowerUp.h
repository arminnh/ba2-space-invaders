/*
 * PowerUp.h
 *
 *  Created on: Nov 22, 2013
 *      Author: Armin Halilovic
 */

#ifndef POWERUP_H_
#define POWERUP_H_

#include <memory>
#include "Entity.h"
#include "Cannon.h"

namespace Entities {

/**
 * Represents a power-up that helps the player.
 */
class PowerUp : public Entity {
private:
	int type;

public:
	/// Default constructor.
	PowerUp();

	/// Parametrized constructor.
	PowerUp(int, int, int, int, int);

	/// Destructor.
	virtual ~PowerUp();

	/// Return the type of the power up.
	int getType() const;
	/// Set the type of the power up.
	void setType(int);

	/// Check whether or not a cannon touches the power up.
	bool contains(std::shared_ptr<Cannon>);
};

} /* namespace Entities */

#endif /* POWERUP_H_ */
