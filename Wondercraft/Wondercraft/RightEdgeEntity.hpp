#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class RightEdgeEntity : public Entity {
public:
	RightEdgeEntity(sf::Vector2f& position, float height);

	//ignores collisions with RightEdgeEntity, TopEdgeEntity, and BottomEdgeEntity
	virtual bool collisionCalc(float& step, float deltaTime, Entity&);

	virtual float getTop();
	virtual float getBottom();

private:
	float height;
};