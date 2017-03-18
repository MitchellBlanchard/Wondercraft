#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "RectangleEntity.hpp"

namespace EnemyType {
	enum EnemyType {
		GOOBER,
		GHOST,
		GOBLIN
	};
}

class Enemy : public RectangleEntity {
public:
	Enemy(sf::Vector2f spawn, int, float);
	void updatePosition(float dt, Player* p);

	float health;
	EnemyType::EnemyType type;

private:
	const float TILE_SIZE;
};