#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Enemy : public sf::Transformable {
public:
	Enemy(sf::Vector2f pos, sf::Vector2f dim);
	void updatePosition(float dt, Player* p);
	void collision();

protected:
	float rx, ry;
	sf::Vector2f velocity;

private:

};