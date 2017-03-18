#include "LevelItem.hpp"

#include <iostream>
LevelItem::LevelItem(ItemType::ItemType type, sf::Vector2f& position) : type(type), position(position) { std::cout << type << std::endl; }