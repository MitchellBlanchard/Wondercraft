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

	if (model->gameState == 1) {

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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (model->player->projectileTimer == 0) {
				sf::Vector2f mouseVec = sf::Vector2f(((float)sf::Mouse::getPosition(window).x / (float)64), ((float)sf::Mouse::getPosition(window).y / (float)64));
				sf::Vector2f playerVec = sf::Vector2f(((-view->getStartingPos().x)*view->TILE_SIZE) + (model->player->position.x * view->TILE_SIZE), ((model->player->position.y * view->TILE_SIZE) - (view->getStartingPos().y*view->TILE_SIZE)));

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
				model->playerProjectiles.push_back(new Projectile(model->player->position, view->getStartingPos(), playerVec, mouseVec, view->TILE_SIZE, projectileType));
			} 
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			model->gameState = 2;
			model->menu.selectedLoc.x = 0;
			model->menu.selectedLoc.y = 0;
		}
		else {
			model->player->setVelocity(sf::Vector2f(0, model->player->getVelocity().y));
		}
	}

	//this shit currently flips too fast. gotta set an individual limit for moving on this menu i guess :V
	//also, fuck this garbage, im shit im so sorry
	else if (model->gameState == 2) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
			model->gameState = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (model->menu.menuSide == 1) { //left menu
				if (model->menu.selectedLoc.y - 1 >= 0)
					model->menu.selectedLoc.y -= 1;
			}
			else if (model->menu.menuSide == 2) {
				//nothing happens if you hit up on crafting menu
			}
			else if (model->menu.menuSide == 3) {
				if (model->menu.selectedLoc.y - 1 >= 0) //stay in menu, just move up
					model->menu.selectedLoc.y -= 1;
				else if (model->menu.selectedLoc.x <= 4) { //gotta go to equip menus
					model->menu.menuSide = 1;
					model->menu.selectedLoc.y = 2;
				}
				else { //gotta go to crafting
					model->menu.menuSide = 2;
					model->menu.selectedLoc.x = 0;
					model->menu.selectedLoc.y = 0;
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (model->menu.menuSide == 1) { //left menu
				//nothing happens if you hit left in left menu
			}
			else if (model->menu.menuSide == 2) { //right menu
				if (model->menu.selectedLoc.x - 1 >= 0) {
					model->menu.selectedLoc.x -= 1;
				}
				else {
					model->menu.menuSide = 1;
					model->menu.selectedLoc.y = 2;
				}
			}
			else if (model->menu.menuSide == 3) {
				if (model->menu.selectedLoc.x - 1 >= 0)
					model->menu.selectedLoc.x -= 1;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (model->menu.menuSide == 1) { //in left menu, go to right menu
				model->menu.menuSide = 2;
			}
			else if (model->menu.menuSide == 2) { //in right menu 
				if (model->menu.selectedLoc.x + 1 < 3) {
					model->menu.selectedLoc.x += 1;
				}
			}
			else if (model->menu.menuSide == 3) { //in bottom menu
				if (model->menu.selectedLoc.x + 1 < 10)
					model->menu.selectedLoc.x += 1;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (model->menu.menuSide == 1){ //in left menu
				if (model->menu.selectedLoc.y + 1 < 3) {
					model->menu.selectedLoc.y += 1;
				}
				else {
					model->menu.menuSide = 3;
				}
			}
			else if (model->menu.menuSide == 2) { //in right menu 
				model->menu.menuSide = 3;
			}
			else if (model->menu.menuSide == 3) { //in the bottom menu
				if (model->menu.selectedLoc.y + 1 < 3)
					model->menu.selectedLoc.y += 1;
			}
			
		}
	}
}

bool Controller::isRunning() const {
	return view->getWindow().isOpen();
}