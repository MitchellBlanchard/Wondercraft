#include "Menu.hpp"

#include "Model.hpp"

Menu::Menu() {
	menuSide = MenuSide::INVENTORY;

	equipmentIndex = 0;
	craftingIndex = 0;
	inventoryIndex = sf::Vector2i(0, 0);

	selected = sf::Vector2i(-1, -1);
}

ItemType::ItemType Menu::craftedItem() {

	if (craftingContains(ItemType::AIR_GEM) && craftingContains(ItemType::BASIC_HAT)) {
		return ItemType::AIR_HAT;
	}

	else if (craftingContains(ItemType::WATER_GEM) && craftingContains(ItemType::BASIC_HAT)) {
		return ItemType::WATER_HAT;
	}

	else if (craftingContains(ItemType::FIRE_GEM) && craftingContains(ItemType::BASIC_HAT)) {
		return ItemType::FIRE_HAT;
	}

	else if (craftingContains(ItemType::EARTH_GEM) && craftingContains(ItemType::BASIC_HAT)) {
		return ItemType::EARTH_HAT;
	}

	else if (craftingContains(ItemType::AIR_GEM) && craftingContains(ItemType::BASIC_ROBE)) {
		return ItemType::AIR_ROBE;
	}

	else if (craftingContains(ItemType::WATER_GEM) && craftingContains(ItemType::BASIC_ROBE)) {
		return ItemType::WATER_ROBE;
	}

	else if (craftingContains(ItemType::FIRE_GEM) && craftingContains(ItemType::BASIC_ROBE)) {
		return ItemType::FIRE_ROBE;
	}

	else if (craftingContains(ItemType::EARTH_GEM) && craftingContains(ItemType::BASIC_ROBE)) {
		return ItemType::EARTH_ROBE;
	}
	else if (craftingContains(ItemType::AIR_GEM) && craftingContains(ItemType::BASIC_STAFF)) {
		return ItemType::AIR_STAFF;
	}

	else if (craftingContains(ItemType::WATER_GEM) && craftingContains(ItemType::BASIC_STAFF)) {
		return ItemType::WATER_STAFF;
	}

	else if (craftingContains(ItemType::FIRE_GEM) && craftingContains(ItemType::BASIC_STAFF)) {
		return ItemType::FIRE_STAFF;
	}

	else if (craftingContains(ItemType::EARTH_GEM) && craftingContains(ItemType::BASIC_STAFF)) {
		return ItemType::EARTH_STAFF;
	}

	else if (craftingContains(ItemType::WARM_STONE) && craftingContains(ItemType::DRY_STONE)) {
		//gives fire gem
		return ItemType::FIRE_GEM;
	}

	else if (craftingContains(ItemType::WARM_STONE) && craftingContains(ItemType::WET_STONE)) {
		//gives air
		return ItemType::AIR_GEM;
	}

	else if (craftingContains(ItemType::COOL_STONE) && craftingContains(ItemType::DRY_STONE)) {
		//gives earth
		return ItemType::EARTH_GEM;
	}

	else if (craftingContains(ItemType::COOL_STONE) && craftingContains(ItemType::WET_STONE)) {
		//gives water
		return ItemType::WATER_GEM;
	}

	else {
		return ItemType::NONE;
	}
}

bool Menu::craftingContains(ItemType::ItemType a) {
	return (craftingSlots[0] == a || craftingSlots[1] == a);
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
	else {
		ItemType::ItemType temp;

		

		switch (selectedSide) {
		case MenuSide::EQUIPMENT:
			if (typesMatch(model)) {
				temp = model->player->equipment[selected.y];
				//model->player->equipment[selected.y] = 
			}
			break;

		case MenuSide::CRAFTING:
			
			break;

		case MenuSide::INVENTORY:
			
			break;

		default:
			break;
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
		else if (menuSide == MenuSide::INVENTORY && selected == inventoryIndex) {
			return true;
		}
	}

	//source is equipment
	if (selectedSide == MenuSide::EQUIPMENT) {
		if (menuSide == MenuSide::EQUIPMENT) {
			return false;
		}
		else if (menuSide == MenuSide::CRAFTING && craftingIndex < 2 && typesMatch(model)) {
			return true;
		}
		else if (menuSide == MenuSide::INVENTORY && typesMatch(model)) {
			return true;
		}
	}
	//source is crafting input
	else if (selectedSide == MenuSide::CRAFTING && selected.x < 2) {
		if (menuSide == MenuSide::EQUIPMENT && selected.x < 2 && typesMatch(model)) {

		}
		else if (menuSide == MenuSide::CRAFTING && selected.x < 2) {

		}
		else if (menuSide == MenuSide::INVENTORY) {
			return selected.x < 2 || currentItem(model) == ItemType::NONE;
		}
	}
	//source is crafting output
	else if (selectedSide == MenuSide::CRAFTING && selected.x == 2) {
		if (menuSide == MenuSide::EQUIPMENT) {
			return false;
		}
		else if (menuSide == MenuSide::CRAFTING && currentItem(model) == ItemType::NONE) {
			return false;
		}
		else if (menuSide == MenuSide::INVENTORY && currentItem(model) == ItemType::NONE) {
			
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