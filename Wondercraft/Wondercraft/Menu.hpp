#pragma once

#include <SFML/Graphics.hpp>

namespace MenuSide {
	enum MenuSide {
		EQUIPMENT,
		INVENTORY,
		CRAFTING
	};
}

class Menu {
public:
	Menu();

	MenuSide::MenuSide menuSide;

	int equipmentIndex;
	int craftingIndex;
	sf::Vector2i inventoryIndex;

	void selectionLeft();
	void selectionRight();
	void selectionUp();
	void selectionDown();
};
