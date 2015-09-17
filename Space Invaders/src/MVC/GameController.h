/*
 * GameController.h
 *
 *  Created on: Dec 4, 2013
 *      Author: Armin Halilovic
 */

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "GameModel.h"
#include "GameView.h"
#include <memory>

namespace MVC {

/**
 * GameController is the "Controller" part of the MVC pattern used for the game.
 * GameController contains GameModel and GameView and makes these interact with each other through a player.
 */
class GameController {
private:
	std::shared_ptr<GameModel> model;
	std::shared_ptr<GameView> view;

	bool paused;
	double enemySpeed;

public:
	/// Parametrized constructor.
	GameController(std::shared_ptr<GameModel>, std::shared_ptr<GameView>);

	/// Destructor.
	~GameController();

	/// Handle all events.
	void handleEvents();
	/// Handle the keyboard input. (Separated from handleEvents to optimize for live input.)
	void handleKeyboard();

	/// Start the game.
	void game();
	/// Start the intro for the game.
	void intro();
	/// Restart the game.
	void restart();
};

} /* namespace MVC */

#endif /* GAMECONTROLLER_H_ */
