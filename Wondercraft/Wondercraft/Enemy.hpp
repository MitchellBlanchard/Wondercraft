#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Entity.hpp"

class Enemy : public Entity {
public:
	Enemy(sf::Vector2f spawn);
	void updatePosition(float dt, Player* p);

	float collisionCalc(float deltaTime, Entity&);

	float rx, ry;

protected:
	sf::Vector2f velocity;

private:

};