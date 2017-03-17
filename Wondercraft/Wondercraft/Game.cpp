#include "Game.hpp"
#include <iostream>

Game::Game() : view(&model), controller(&model, &view) {}

void Game::loop() {
	while (controller.isRunning()) {
		//take input from controller
		controller.inputs();

		//limit update rate
		if (lastUpdate.getElapsedTime() > sf::seconds(1.0f / updateFPS)) {
			//update model by delta time
			model.update(lastUpdate.restart().asSeconds());
		}

		//limit render rate
		if (lastRender.getElapsedTime() > sf::seconds(1.0f / renderFPS)) {
			//render the view
			lastRender.restart();
			view.render(model.gameState);
		}
	}
}