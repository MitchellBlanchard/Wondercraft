#pragma once

#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

class Game {
public:
	Game();

	void loop();

private:
	Model model;
	View view;
	Controller controller;

	sf::Clock lastUpdate;
	sf::Clock lastRender;

	const float updateFPS = 100.0f;
	const float renderFPS = 60.0f;
};