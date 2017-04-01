#pragma once

#include <SFML/Graphics.hpp>

// Entity represents a collideable object in the game world
class Entity {
public:
	Entity(sf::Vector2f& position = sf::Vector2f());

	sf::Vector2f getVelocity();
	virtual void setVelocity(sf::Vector2f&);

	sf::Vector2f getPosition();
	virtual void setPosition(sf::Vector2f&);

	//returns true if the bounding box of both entities intersect
	bool checkAABB(Entity&);

	//returns true if the bounding box of the given entity intersects with the bounding box
	//that contains this entity at its starting and ending position
	bool checkMovingAABB(float deltaTime, Entity&);

	//outputs into 'step' the fraction of the frame step until colliding with the given object, or 1 if there is no collision
	//returns whether or not there is a collision
	virtual bool collisionCalc(float& step, float deltaTime, Entity&)=0;

	virtual float getLeft();
	virtual float getTop();
	virtual float getRight();
	virtual float getBottom();
	sf::Vector2f getSize();

protected:
	sf::Vector2f velocity;
	sf::Vector2f position;
};