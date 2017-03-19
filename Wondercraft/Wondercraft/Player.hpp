#pragma once

#include <SFML/Graphics.hpp>

#include "RectangleEntity.hpp"
#include "ItemType.hpp"

class Model;

class Player : public RectangleEntity {
public:
	Player(sf::Vector2f position);

	void update(float deltaTime, Model*);

	float getHealth();

	float projectileTimer;
	float invinceFrames;

	bool facingRight;

	ItemType::ItemType equipment[3]; // hat, robe, staff

private:
	float health;
};