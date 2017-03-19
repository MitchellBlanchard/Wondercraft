#pragma once

#include <SFML/Graphics.hpp>

#include "ItemType.hpp"

class Model;

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

	MenuSide::MenuSide selectedSide;
	sf::Vector2i selected;

	ItemType::ItemType craftingSlots[2];

	void selectionLeft();
	void selectionRight();
	void selectionUp();
	void selectionDown();

	void select(Model*);

	ItemType::ItemType craftedItem();

	bool craftingContains(ItemType::ItemType);

private:
	bool canSwap(Model*);
	ItemType::ItemType currentItem(Model*);
	ItemType::ItemType selectedItem(Model*);
	bool typesMatch(Model*);
};
