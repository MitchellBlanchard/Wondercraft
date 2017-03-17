 #pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "LeftEdgeEntity.hpp"
#include "RightEdgeEntity.hpp"
#include "TopEdgeEntity.hpp"
#include "BottomEdgeEntity.hpp"

class RectangleEntity : public Entity {
public:
	RectangleEntity(sf::Vector2f& position, sf::Vector2f& size);

	//also sets the velocity of all four edges
	virtual void setVelocity(sf::Vector2f&);

	//also sets the position of all four edges
	virtual void setPosition(sf::Vector2f&);

	virtual bool collisionCalc(float& step, float deltaTime, Entity&);

	virtual float getLeft();
	virtual float getTop();
	virtual float getRight();
	virtual float getBottom();

private:
	LeftEdgeEntity leftEdge;
	RightEdgeEntity rightEdge;
	TopEdgeEntity topEdge;
	BottomEdgeEntity bottomEdge;
};