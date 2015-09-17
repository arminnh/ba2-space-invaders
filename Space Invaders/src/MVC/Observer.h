/*
 * Observer.h
 *
 *  Created on: Dec 11, 2013
 *      Author: Armin Halilovic
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

namespace MVC {

// Forward declaration of GameModel to be used in Observer.
class GameModel;

/**
 * Observer interface for the obsever pattern.
 */
class Observer {
public:
	virtual ~Observer() { }

	virtual void notifyReset() = 0;
	virtual void notifyUFO(GameModel*) = 0;
	virtual void notifyPlayer(GameModel*) = 0;
	virtual void notifyEnemies(GameModel*) = 0;
	virtual void notifyPowerUp(GameModel*) = 0;
	virtual void notifyBullets(GameModel*) = 0;
	virtual void notifyText(GameModel* model) = 0;
	virtual void notifyShields(GameModel* model) = 0;
};

} /* namespace MVC */

#endif /* OBSERVER_H_ */
