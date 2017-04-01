#pragma once

#include <SFML/Graphics.hpp>

#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

// Control flow and logic for the game loop.
// Has access to the entire Model-View-Controller architecture.
class Game {
public:
	Game();

	//begins the game loop
	void loop();

private:
	Model model;
	View view;
	Controller controller;

	sf::Clock lastUpdate;
	sf::Clock lastRender;

	const float updateFPS;
	const float renderFPS;
};