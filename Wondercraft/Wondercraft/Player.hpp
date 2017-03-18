#pragma once

#include <SFML/Graphics.hpp>

#include "RectangleEntity.hpp"
#include "ItemType.hpp"

class Model;

class Player : public RectangleEntity {
public:
	Player(sf::Vector2f position);

	void update(float deltaTime, Model*);

	float projectileTimer;

	bool facingRight;

	ItemType::ItemType hat, robe, staff;

private:
	
};