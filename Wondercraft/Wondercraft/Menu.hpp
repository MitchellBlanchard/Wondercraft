#pragma once

#include <SFML/Graphics.hpp>

#include "ItemType.hpp"

class Model;

// There are three sections in the inventory menu
namespace MenuSide {
	enum MenuSide {
		EQUIPMENT,
		INVENTORY,
		CRAFTING
	};
}

// Handles interactions with the inventory, equipment, and crafting system.
// This is accessed by the player through the inventory pause menu.
class Menu {
public:
	Menu();

	//the current index is on this section of the menu
	MenuSide::MenuSide menuSide;

	//the most recent index location in each section
	int equipmentIndex;
	int craftingIndex;
	sf::Vector2i inventoryIndex;

	//the current selection is in this section of the menu
	MenuSide::MenuSide selectedSide;
	//the current selection location within its section
	sf::Vector2i selected;

	//the items currently in the crafting input slots
	ItemType::ItemType craftingSlots[2];

	//moves the current index
	void selectionLeft();
	void selectionRight();
	void selectionUp();
	void selectionDown();

	//selects an item or moves an already-selected item
	void select(Model*);

	//returns the item that would be output by combining the two items in the crafting input slots
	ItemType::ItemType craftedItem();

	//returns true if the two items in the crafting input slots are able to be combined
	bool craftingContains(ItemType::ItemType);

private:
	//returns true if the selected item can be successfully moved to the current index location
	bool canSwap(Model*);

	//returns the item at the current index
	ItemType::ItemType currentItem(Model*);

	//returns the item currently selected
	ItemType::ItemType selectedItem(Model*);

	//for equipping items,
	//returns true if the currentItem() and selectedItem() are of the same equipable type
	bool typesMatch(Model*);
};
