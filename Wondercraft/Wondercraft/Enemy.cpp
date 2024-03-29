#include "Enemy.hpp"

#include "Model.hpp"

Enemy::Enemy(sf::Vector2f spawn, EnemyType::EnemyType type, sf::Vector2f size) : RectangleEntity(spawn - sf::Vector2f(size.x/2, size.y/2), size), TILE_SIZE(TILE_SIZE) {
	this->type = type;
	
	if (type == EnemyType::GOOBER) {
		//we need to spawn a goober
		health = 15;
		damage = 10;
	}
	else if (type == EnemyType::GHOST) {
		//we need to spawn a ghost
		health = 10;
		damage = 7;
	}
	else if (type == EnemyType::GOBLIN) {
		//we need to spawn a goblin
		health = 10;
		damage = 7;
		velocity = sf::Vector2f(2, 0);
	}
}

void Enemy::update(float dt, Player* player, Model* model) {
	//std::cout << type << std::endl;
	if (type == EnemyType::GOOBER) {
		//move like a goober
	}
	else if (type == EnemyType::GHOST) {
		//move like a ghost
		sf::Vector2f ghostVec = sf::Vector2f(position.x/**TILE_SIZE*/, position.y/**TILE_SIZE*/);
		sf::Vector2f playerVec = sf::Vector2f(player->getPosition().x/**TILE_SIZE*/, player->getPosition().y/**TILE_SIZE*/);
		sf::Vector2f diffVector = ghostVec - playerVec;

		float magnitude = sqrt(pow(diffVector.x, 2) + pow(diffVector.y, 2));

		if (magnitude < 10) {
			velocity = sf::Vector2f(-(diffVector.x / magnitude) * 2, -(diffVector.y / magnitude) * 2);

			setPosition(position + velocity*dt);
		}

		if (magnitude < 3) {
			velocity.x = 0;
		}
	}
	else if (type == EnemyType::GOBLIN) {
		//move like a goblin

		//check if we should switch directions

		//check collisions with the tiles
		for (int i = getLeft(); i < (getRight()); i++) {
			for (int j = getTop(); j < (getBottom()); j++) {
				//std::cout << "Colliding with tiles" << std::endl;
				//we need to go through the ones that we are close to
				if (i > 0 && i < model->levelWidth && j > 0 && j < model->levelHeight) {
					if (model->mapTiles[i][j] != NULL) {
						bool collided = checkAABB(*model->mapTiles[i][j]);

						if (collided) {
							velocity = sf::Vector2f(velocity.x * -1, velocity.y * -1);
						}
					}
				}
			}
		}

		bool grounded = false;
		sf::Vector2f checkPoints[]{
			sf::Vector2f(getLeft() + 0.01, getBottom() + 0.01),
			sf::Vector2f(getRight() - 0.01, getBottom() + 0.01) };


		Entity* tile = model->mapTiles[int(floor(checkPoints[0].x))][int(floor(checkPoints[0].y))];
		if (tile != NULL)
			grounded = true;

		if (!grounded) {
			velocity = sf::Vector2f(2, 0);
		}

		grounded = false;
		tile = model->mapTiles[int(floor(checkPoints[1].x))][int(floor(checkPoints[1].y))];
		if (tile != NULL)
			grounded = true;

		if (!grounded) {
			velocity = sf::Vector2f(-2, 0);
		}

		setPosition(position + velocity*dt);
	}

	right = (velocity.x > 0);
}