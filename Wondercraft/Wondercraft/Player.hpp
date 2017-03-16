#pragma once

#include <SFML/Graphics.hpp>

#include "RectangleEntity.hpp"

class Model;

class Player : public RectangleEntity {
public:
	Player(sf::Vector2f position);

	void update(float deltaTime, Model*);

private:
	
};