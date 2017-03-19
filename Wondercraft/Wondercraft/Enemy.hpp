#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "RectangleEntity.hpp"

class Model;

namespace EnemyType {
	enum EnemyType {
		GOOBER,
		GHOST,
		GOBLIN
	};
}

class Enemy : public RectangleEntity {
public:
	Enemy(sf::Vector2f spawn, int, sf::Vector2f);
	void updatePosition(float dt, Player* p, Model* m);

	float health, damage;
	EnemyType::EnemyType type;

	bool right;

private:
	const float TILE_SIZE;
};