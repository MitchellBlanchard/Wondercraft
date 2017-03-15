#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
	Entity(sf::Vector2f& spawn);

	sf::Vector2f position;
	sf::Vector2f velocity;

	//returns true if the bounding box of both entities intersect
	bool checkAABB(Entity&);

	//returns true if the bounding box of the given entity intersects with the bounding box
	//that contains this entity at its starting and ending position
	bool checkMovingAABB(float deltaTime, Entity&);

	//returns the fraction of the frame step until colliding with the given object
	//returns a negative value if there is no collision
	virtual float collisionCalc(float deltaTime, Entity&)=0;

	virtual sf::Vector2f getSize();
	virtual float getLeft();
	virtual float getTop();
	virtual float getRight();
	virtual float getBottom();
};