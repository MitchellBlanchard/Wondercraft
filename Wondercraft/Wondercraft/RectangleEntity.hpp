#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class RectangleEntity : public Entity {
public:
	RectangleEntity(sf::Vector2f& position, sf::Vector2f& size);

	//returns the fraction of the frame step until colliding with the given object
	//returns a negative value if there is no collision
	virtual float collisionCalc(float deltaTime, Entity&);

	virtual float getLeft();
	virtual float getTop();
	virtual float getRight();
	virtual float getBottom();

	sf::Vector2f getSize();
};