#pragma once

#include "Model.hpp"

class View {
public:
	View(const Model*);

	sf::RenderWindow& getWindow();
	void render();

private:
	const Model* model;

	sf::RenderWindow window;
};