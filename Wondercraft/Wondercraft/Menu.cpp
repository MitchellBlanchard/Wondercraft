#include "Menu.hpp"

#include "Model.hpp"

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

void Menu::select(Model* model) {
	//select an item if there is an item to select and no current selection
	if (selected == sf::Vector2i(-1, -1)) {
		if (currentItem(model) != ItemType::NONE) {
			selectedSide = menuSide;
			if (menuSide == MenuSide::EQUIPMENT)
				selected = sf::Vector2i(0, equipmentIndex);
			else if (menuSide == MenuSide::CRAFTING)
				selected = sf::Vector2i(craftingIndex, 0);
			else if (menuSide == MenuSide::INVENTORY)
				selected = inventoryIndex;
		}
	}
	//move items and remove selection
	else if(canSwap(model)){
		ItemType::ItemType temp;

		//source is equipment
		if (selectedSide == MenuSide::EQUIPMENT) {
			temp = model->player->equipment[selected.y];
			model->player->equipment[selected.y] = currentItem(model);
		}
		//source is crafting input
		else if (selectedSide == MenuSide::CRAFTING && selected.x < 2) {
			temp = craftingSlots[selected.x];
			craftingSlots[selected.x] = currentItem(model);
		}
		//source is crafting output
		else if (selectedSide == MenuSide::CRAFTING && selected.x == 2) {
			if (menuSide != MenuSide::CRAFTING || craftingIndex < 2) {
				temp = craftedItem();
				craftingSlots[0] = ItemType::NONE;
				craftingSlots[1] = ItemType::NONE;
			}
		}
		//source is inventory
		else if (selectedSide == MenuSide::INVENTORY) {
			temp = model->inventory[selected.x][selected.y];
			model->inventory[selected.x][selected.y] = currentItem(model);
		}


		//destination is equipment
		if (menuSide == MenuSide::EQUIPMENT) {
			model->player->equipment[equipmentIndex] = temp;
			selected = sf::Vector2i();
		}
		//destination is crafting input
		else if (menuSide == MenuSide::CRAFTING && selected.x < 2) {
			craftingSlots[craftingIndex] = temp;
			selected = sf::Vector2i();
		}
		//destination is crafting output
		else if (menuSide == MenuSide::CRAFTING && selected.x == 2) {
			selected = sf::Vector2i();
		}
		//destination is inventory
		else if (menuSide == MenuSide::INVENTORY) {
			model->inventory[inventoryIndex.x][inventoryIndex.y] = temp;
			selected = sf::Vector2i();
		}
	}
}

bool Menu::canSwap(Model* model) {
	//return true if it's the same position
	if (selectedSide == menuSide) {
		if (menuSide == MenuSide::EQUIPMENT && selected.y == equipmentIndex) {
			return true;
		}
		else if (menuSide == MenuSide::CRAFTING && selected.x < 2 && craftingIndex < 2) {
			return true;
		}
		else if (menuSide == MenuSide::CRAFTING && selected.x == 2 && craftingIndex == 2) {
			return true;
		}
		else if (menuSide == MenuSide::INVENTORY && selected == inventoryIndex) {
			return true;
		}
	}

	//source is equipment
	if (selectedSide == MenuSide::EQUIPMENT) {
		if (menuSide == MenuSide::EQUIPMENT) {
			return false;
		}
		else if (menuSide == MenuSide::CRAFTING) {
			return craftingIndex < 2 && typesMatch(model);
		}
		else if (menuSide == MenuSide::INVENTORY) {
			return typesMatch(model);
		}
	}
	//source is crafting input
	else if (selectedSide == MenuSide::CRAFTING && selected.x < 2) {
		if (menuSide == MenuSide::EQUIPMENT) {
			return typesMatch(model);
		}
		else if (menuSide == MenuSide::CRAFTING) {
			return craftingIndex < 2;
		}
		else if (menuSide == MenuSide::INVENTORY) {
			return true;
		}
	}
	//source is crafting output
	else if (selectedSide == MenuSide::CRAFTING && selected.x == 2) {
		if (menuSide == MenuSide::EQUIPMENT) {
			return false;
		}
		else if (menuSide == MenuSide::CRAFTING) {
			return currentItem(model) == ItemType::NONE;
		}
		else if (menuSide == MenuSide::INVENTORY) {
			return currentItem(model) == ItemType::NONE;
		}
	}
	//source is inventory
	else if (selectedSide == MenuSide::INVENTORY) {
		if (menuSide == MenuSide::EQUIPMENT) {
			return typesMatch(model);
		}
		else if (menuSide == MenuSide::CRAFTING) {
			return craftingIndex < 2;
		}
		else if (menuSide == MenuSide::INVENTORY) {
			return true;
		}
	}

	return false;
}

ItemType::ItemType Menu::currentItem(Model* model) {
	switch (menuSide) {
	case MenuSide::EQUIPMENT:
		return model->player->equipment[equipmentIndex];

	case MenuSide::CRAFTING:
		if(craftingIndex < 2)
			return craftingSlots[craftingIndex];
		else return craftedItem();

	case MenuSide::INVENTORY:
		return model->inventory[inventoryIndex.x][inventoryIndex.y];

	default:
		return ItemType::NONE;
	}
}

ItemType::ItemType Menu::selectedItem(Model* model) {
	switch (selectedSide) {
	case MenuSide::EQUIPMENT:
		return model->player->equipment[selected.y];

	case MenuSide::CRAFTING:
		if (selected.x < 2)
			return craftingSlots[selected.x];
		else return craftedItem();

	case MenuSide::INVENTORY:
		return model->inventory[selected.x][selected.y];

	default:
		return ItemType::NONE;
	}
}

bool Menu::typesMatch(Model* model) {
	return     isHat(currentItem(model))   == isHat(selectedItem(model))
			&& isRobe(currentItem(model))  == isRobe(selectedItem(model))
			&& isStaff(currentItem(model)) == isStaff(selectedItem(model));
}