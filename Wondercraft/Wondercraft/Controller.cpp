#include "Controller.hpp"
#include <iostream>
Controller::Controller(Model* model, View* view) {
	this->model = model;
	this->view = view;
}

void Controller::inputs() {
	sf::RenderWindow& window = view->getWindow();

	//poll for window events
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		
		if (model->camera.y - 0.1 - (view->windowSize.y/2) > 0) {
			model->camera.y -= 0.1;
		}
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (model->camera.y + 0.1 + (view->windowSize.y / 2) < (model->levelHeight-1) * view->TILE_SIZE) {
			model->camera.y += 0.1;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (model->camera.x - 0.1 - (view->windowSize.x / 2) > -((model->levelWidth - 1) * view->TILE_SIZE - view->windowSize.x)) {
			model->camera.x -= 0.1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (model->camera.x + 0.1 - (view->windowSize.x / 2) < 0){
			model->camera.x += 0.1;
		}
	}
}

bool Controller::isRunning() const {
	return view->getWindow().isOpen();
}