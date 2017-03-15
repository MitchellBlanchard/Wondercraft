#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class LeftEdgeEntity : public Entity {
public:
	LeftEdgeEntity(sf::Vector2f& position, float height);

	virtual float collisionCalc(float deltaTime, Entity&);

	virtual sf::Vector2f getSize();
	virtual float getTop();
	virtual float getBottom();

private:
	float height;
};