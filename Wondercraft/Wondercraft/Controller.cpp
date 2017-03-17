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

	float speed = 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (model->playerIsGrounded()) {
			model->player->setVelocity(sf::Vector2f(model->player->getVelocity().x, -10));
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		model->player->setVelocity(sf::Vector2f(-speed, model->player->getVelocity().y));
		model->player->facingRight = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		model->player->setVelocity(sf::Vector2f(speed, model->player->getVelocity().y));
		model->player->facingRight = true;
	}
	else {
		model->player->setVelocity(sf::Vector2f(0, model->player->getVelocity().y));
	}
}

bool Controller::isRunning() const {
	return view->getWindow().isOpen();
}