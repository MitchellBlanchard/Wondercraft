#include "Controller.hpp"

#include <SFML/Graphics.hpp>
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

	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (model->camera.y - 0.01 - (view->windowSize.y/2) > 0) {
			model->camera.y -= 0.01;
		}
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (model->camera.y + 0.01 + (view->windowSize.y / 2) < (model->levelHeight) * view->TILE_SIZE) {
			model->camera.y += 0.01;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (model->camera.x + 0.01 + (view->windowSize.x / 2) < (model->levelWidth - 1) * view->TILE_SIZE) {
			model->camera.x += 0.01;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (model->camera.x - 0.01 - (view->windowSize.x / 2) > 0) {
			model->camera.x -= 0.01;
		}
	}
	*/
	float speed = 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (model->playerIsGrounded()) {
			model->player->setVelocity(sf::Vector2f(model->player->getVelocity().x, -20));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		//do nothing on Down right now
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		model->player->setVelocity(sf::Vector2f(-speed, model->player->getVelocity().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		model->player->setVelocity(sf::Vector2f(speed, model->player->getVelocity().y));
	}
	else {
		model->player->setVelocity(sf::Vector2f(0, model->player->getVelocity().y));
	}
}

bool Controller::isRunning() const {
	return view->getWindow().isOpen();
}