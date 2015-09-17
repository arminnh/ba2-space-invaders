/*
 * Main.cpp
 *
 *  Created on: Nov 22, 2013
 *      Author: Armin Halilovic
 */

#include "MVC/GameView.h"
#include "MVC/GameModel.h"
#include "MVC/GameController.h"
#include <iostream>

int main () {

	try {
		std::shared_ptr<MVC::GameModel> model (new MVC::GameModel);
		std::shared_ptr<MVC::GameView> view (new MVC::GameView);
		std::shared_ptr<MVC::GameController> controller (new MVC::GameController(model, view));

		model->registerObserver(view);
		model->notifyObserversAll();

		controller->intro();
		controller->game();

	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
