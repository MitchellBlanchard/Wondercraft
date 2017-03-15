#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "RectangleEntity.hpp"

class Enemy : public RectangleEntity {
public:
	Enemy(sf::Vector2f spawn);
	void updatePosition(float dt, Player* p);

protected:
	sf::Vector2f velocity;

private:

};