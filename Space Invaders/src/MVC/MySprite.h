/*
 * MySprite.h
 *
 *  Created on: Dec 11, 2013
 *      Author: Armin Halilovic
 */

#ifndef MYSPRITE_H_
#define MYSPRITE_H_

#include <SFML/Graphics.hpp>

namespace sf {

/**
 * MySprite class extends sprite to have an animation count.
 */
class MySprite : public Sprite {
private:
	int animation;

public:
	/// Default  constructor.
	MySprite() : Sprite() { animation = 0; }

	/// Destructor.
	~MySprite() { }

	/// Set the animation count.
	void setAnimation(int animation)  { this->animation = animation; }

	/// Return the animation count.
	int getAnimation() const { return this->animation; }
};

} /* namespace sf*/

#endif /* MYSPRITE_H_ */
