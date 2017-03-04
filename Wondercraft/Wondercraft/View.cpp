#include "View.hpp"

View::View(const Model* model) {

	windowSize = sf::Vector2f(960, 540);

	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Wondercraft");

	initSpriteArray();

	this->model = model;
}

void View::initSpriteArray() {
	//initialize the sprites
	displaySprites.resize(int(ceil(windowSize.y / 64) + 1));
	
	for (int i = 0; i < displaySprites.size(); i++) {
		displaySprites[i].resize(int(ceil(windowSize.x / 64) + 1));
		for (int j = 0; j < displaySprites[i].size(); j++) {
			displaySprites[i][j] = sf::Sprite();
		}
	}
}

sf::RenderWindow& View::getWindow() {
	return window;
}

void View::render() {
	window.clear();
	
	//create a new render state
	sf::RenderStates cameraState = model->camera.getInverseTransform();

	window.display();
}