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

	//returns the fraction of the frame step until colliding with the given object
	//returns a negative value if there is no collision
	virtual float collisionCalc(float deltaTime, Entity&);

	virtual float getLeft();
	virtual float getTop();
	virtual float getRight();
	virtual float getBottom();

	void setSize(sf::Vector2f);

private:
	LeftEdgeEntity leftEdge;
	RightEdgeEntity rightEdge;
	TopEdgeEntity topEdge;
	BottomEdgeEntity bottomEdge;
};