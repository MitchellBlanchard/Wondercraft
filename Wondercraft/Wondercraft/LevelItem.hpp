#pragma once

#include <SFML/Graphics.hpp>

#include "ItemType.hpp"

// Represents an item in the game world (one that is not yet in the player's inventory)
class LevelItem {
public:
	LevelItem(ItemType::ItemType type, sf::Vector2f& position);

	sf::Vector2f position;
	ItemType::ItemType type;
};