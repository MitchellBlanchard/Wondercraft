#include "View.hpp"

View::View(const Model* model) {
	this->model = model;

	window.create(sf::VideoMode(960, 540), "Wondercraft");
}

sf::RenderWindow& View::getWindow() {
	return window;
}

void View::render() {
	window.clear();
	window.draw(*model);
	window.display();
}