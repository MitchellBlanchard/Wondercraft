#pragma once

#include <SFML/Graphics.hpp>

#include "ItemType.hpp"

class LevelItem {
public:
	LevelItem(sf::Vector2f& position);

	sf::Vector2f position;
	ItemType::ItemType type;
};