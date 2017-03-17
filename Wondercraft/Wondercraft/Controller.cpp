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

		else if (event.type == sf::Event::KeyReleased) {
			if (model->gameState == GameState::PLAYING) {
				if (event.key.code == sf::Keyboard::I) {
					model->gameState = INVENTORY;
				}
			}
			else if (model->gameState == GameState::INVENTORY) {
				if (event.key.code == sf::Keyboard::I) {
					model->gameState = PLAYING;
				}
			}
		}
	}

	if (model->gameState == GameState::PLAYING) {
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
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			sf::Vector2f mouseVec = sf::Vector2f(((float)sf::Mouse::getPosition(window).x / (float)64), ((float)sf::Mouse::getPosition(window).y / (float)64));
			sf::Vector2f playerVec = sf::Vector2f(((-view->getStartingPos().x)*view->TILE_SIZE) + (model->player->getPosition().x * view->TILE_SIZE), ((model->player->getPosition().y * view->TILE_SIZE) - (view->getStartingPos().y*view->TILE_SIZE)));

			if (model->player->projectileTimer == 0) {
				int projectileType = 2;

				/*
				if (projectileType == 1) {
				model->player->projectileTimer = 0.5;
				}
				else if (projectileType == 2) {
				model->player->projectileTimer = 1;
				}
				*/

				model->player->projectileTimer = 0.5;
				model->playerProjectiles.push_back(new Projectile(model->player->getPosition(), view->getStartingPos(), playerVec, mouseVec, view->TILE_SIZE, projectileType));
			}
		}
	}
}

bool Controller::isRunning() const {
	return view->getWindow().isOpen();
}