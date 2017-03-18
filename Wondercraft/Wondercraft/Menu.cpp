#include "Menu.hpp"

Menu::Menu() {
	menuSide = MenuSide::INVENTORY;

	equipmentIndex = 0;
	craftingIndex = 0;
	inventoryIndex = sf::Vector2i(0, 0);

	selected = sf::Vector2i(-1, -1);
}

void Menu::selectionLeft() {
	switch (menuSide) {
	case MenuSide::EQUIPMENT:
		break;

	case MenuSide::CRAFTING:
		if (craftingIndex > 0)
			craftingIndex--;
		else menuSide = MenuSide::EQUIPMENT;
		break;

	case MenuSide::INVENTORY:
		if (inventoryIndex.x == 0)
			inventoryIndex.x = 9;
		else inventoryIndex.x--;
		break;

	default:
		break;
	}
}

void Menu::selectionRight() {
	switch (menuSide) {
	case MenuSide::EQUIPMENT:
		menuSide = MenuSide::CRAFTING;
		break;

	case MenuSide::CRAFTING:
		if (craftingIndex < 2)
			craftingIndex++;
		break;

	case MenuSide::INVENTORY:
		if (inventoryIndex.x == 9)
			inventoryIndex.x = 0;
		else inventoryIndex.x++;
		break;

	default:
		break;
	}
}

void Menu::selectionUp() {
	switch (menuSide) {
	case MenuSide::EQUIPMENT:
		if (equipmentIndex > 0)
			equipmentIndex--;
		break;

	case MenuSide::CRAFTING:
		break;

	case MenuSide::INVENTORY:
		if (inventoryIndex.y == 0) {
			if(inventoryIndex.x < 5)
				menuSide = MenuSide::EQUIPMENT;
			else menuSide = MenuSide::CRAFTING;
		}
		else inventoryIndex.y--;
		break;

	default:
		break;
	}
}

void Menu::selectionDown() {
	switch (menuSide) {
	case MenuSide::EQUIPMENT:
		if (equipmentIndex < 2)
			equipmentIndex++;
		else menuSide = MenuSide::INVENTORY;
		break;

	case MenuSide::CRAFTING:
		menuSide = MenuSide::INVENTORY;
		break;

	case MenuSide::INVENTORY:
		if (inventoryIndex.y < 2)
			inventoryIndex.y++;
		break;

	default:
		break;
	}
}

void Menu::select() {
	if (selected == sf::Vector2i(0, 0)) {
		selectedSide = menuSide;
		if (menuSide == MenuSide::EQUIPMENT)
			selected = sf::Vector2i(0, equipmentIndex);
		else if (menuSide == MenuSide::CRAFTING)
			selected = sf::Vector2i(craftingIndex, 0);
		else if (menuSide == MenuSide::INVENTORY)
			selected = inventoryIndex;
	}
}