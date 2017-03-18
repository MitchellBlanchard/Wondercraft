#pragma once

#include <SFML/Graphics.hpp>

#include "ItemType.hpp"

class LevelItem {
public:
	LevelItem(ItemType::ItemType type, sf::Vector2f& position);

	sf::Vector2f position;
	ItemType::ItemType type;
};