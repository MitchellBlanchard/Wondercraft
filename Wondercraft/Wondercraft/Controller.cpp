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
	if (model->gameState == 1) {
		float speed = 5;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (model->playerIsGrounded()) {
				model->player->velocity.y = -20;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			//do nothing on Down right now
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			model->player->velocity.x = -speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			model->player->velocity.x = speed;
		}
		else {
			model->player->velocity.x = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			model->playerShoot();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			model->gameState = 2;
		}
	}
	else if (model->gameState == 2)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
			model->gameState = 1;
		}
	/* lol this shit doesnt work right now :B
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			view->selected.setPosition(view->selected.getPosition().x, view->selected.getPosition().y - view->SQUARE_SIZE_Y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			view->selected.setPosition(view->selected.getPosition().x, view->selected.getPosition().y + view->SQUARE_SIZE_Y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			view->selected.setPosition(view->selected.getPosition().x + view->SQUARE_SIZE_X, view->selected.getPosition().y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			view->selected.setPosition(view->selected.getPosition().x + view->SQUARE_SIZE_X, view->selected.getPosition().y);
		}
		*/
}

bool Controller::isRunning() const {
	return view->getWindow().isOpen();
}