#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Enemy : public sf::Transformable {
public:
	Enemy(sf::Vector2f spawn);
	void updatePosition(float dt, Player* p);

	float rx, ry;

protected:
	sf::Vector2f velocity;

private:

};