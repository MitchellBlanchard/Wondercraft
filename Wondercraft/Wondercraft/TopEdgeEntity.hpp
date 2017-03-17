#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class TopEdgeEntity : public Entity {
public:
	TopEdgeEntity(sf::Vector2f& position, float width);

	virtual bool collisionCalc(float& step, float deltaTime, Entity&);

	virtual float getLeft();
	virtual float getRight();

private:
	float width;
};