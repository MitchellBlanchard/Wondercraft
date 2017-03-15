#include "collisions.hpp"

#include <cmath>

float Collisions::collisionCalc(float deltaTime, Entity& movingEntity, std::vector<Entity*>& stillEntities, std::vector<Entity*>& collidedEntities) {
	collidedEntities.clear();
	
	float nearestCollision = -1;
	for (int i = 0; i < stillEntities.size(); i++) {
		Entity& e = *stillEntities[i];
		float collision = movingEntity.collisionCalc(deltaTime, e);

		if (collision < 0)
			continue;

		if (collision < nearestCollision) {
			nearestCollision = collision;
			collidedEntities.clear();
			collidedEntities.push_back(&e);
		}
		else if (collision == nearestCollision) {
			collidedEntities.push_back(&e);
		}
	}

	return nearestCollision;
}

float Collisions::collisionCalc(float deltaTime, Entity& movingEntity, std::vector<Entity*>& stillEntities) {
	std::vector<Entity*> dummy;
	return collisionCalc(deltaTime, movingEntity, stillEntities, dummy);
}

float Collisions::collisionCalc(float deltaTime, Entity& movingEntity, Entity** stillEntities, int cols, int rows, std::vector<Entity*>& collidedEntities) {
	collidedEntities.clear();

	//determine the bounding box that contains the movingEntity at both its starting and ending positions
	sf::Vector2f v = movingEntity.getVelocity() * deltaTime;

	float leftBound = movingEntity.getLeft();
	if (v.x < 0) leftBound += v.x;

	float rightBound = movingEntity.getRight();
	if (v.x > 0) rightBound += v.x;

	float topBound = movingEntity.getTop();
	if (v.y < 0) topBound += v.y;

	float bottomBound = movingEntity.getBottom();
	if (v.y > 0) bottomBound += v.y;

	//determine the x and y range of tiles touched by the bounding box calculated
	int leftCol = fmax(int(leftBound), 0);
	int rightCol = fmin(int(rightBound), cols - 1);
	int topRow = fmax(int(topBound), 0);
	int bottomRow = fmin(int(bottomBound), rows - 1);

	//only search tiles within the calculated x and y range
	float nearestCollision = -1;
	for (int x = leftCol; x <= rightCol; x++) {
		for (int y = topRow; y <= bottomRow; y++) {
			Entity& e = stillEntities[x][y];
			float collision = movingEntity.collisionCalc(deltaTime, e);

			if (collision < 0)
				continue;

			if (collision < nearestCollision) {
				nearestCollision = collision;
				collidedEntities.clear();
				collidedEntities.push_back(&e);
			}
			else if (collision == nearestCollision) {
				collidedEntities.push_back(&e);
			}
		}
	}

	return nearestCollision;
}

float Collisions::collisionCalc(float deltaTime, Entity& movingEntity, Entity** stillEntities, int cols, int rows) {
	std::vector<Entity*> dummy;
	return collisionCalc(deltaTime, movingEntity, stillEntities, cols, rows, dummy);
}