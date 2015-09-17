/*
 * Entity.h
 *
 *  Created on: Dec 17, 2013
 *      Author: Armin Halilovic
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <memory>

namespace Entities {

// Forward declaration of class Bullet for Entity member function "contains(Bullet *)".
class Bullet;

/**
 * Entity base class that represents all the entities in the game.
 */
class Entity {
private:
	int x, y, width, height;

public:
	/// Default constructor.
	Entity();

	/// Parametrized constructor.
	Entity(int, int, int, int);

	///Destructor.
	virtual ~Entity();

	//Return the x value of the entity.
	int getPositionX() const;
	//Return the y value of the entity.
	int getPositionY() const;
	/// Set the x and y value of the entity.
	void setPosition(int, int);

	/// Return the width of the entity.
	int getWidth() const;
	/// Return the height of the entity.
	int getHeight() const;
	/// Set the width and height of the entity.
	void setDimensions(int, int);

	/// Check whether or not the entity contains a Bullet.
	bool contains(std::shared_ptr<Bullet>);
};

} /* namespace Entities */

#endif /* ENTITY_H_ */
