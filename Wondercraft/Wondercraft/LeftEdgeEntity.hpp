#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class LeftEdgeEntity : public Entity {
public:
	LeftEdgeEntity(sf::Vector2f& position, float height);

	virtual bool collisionCalc(float& step, float deltaTime, Entity&);

	virtual float getTop();
	virtual float getBottom();

private:
	float height;
};