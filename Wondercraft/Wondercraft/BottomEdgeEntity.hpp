#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class BottomEdgeEntity : public Entity {
public:
	BottomEdgeEntity(sf::Vector2f& position, float width);

	//ignores collisions with LeftEdgeEntity, RightEdgeEntity, and BottomEdgeEntity
	virtual bool collisionCalc(float& step, float deltaTime, Entity&);

	virtual float getLeft();
	virtual float getRight();

private:
	float width;
};