#include "collisions.hpp"

#include <cmath>

bool Collisions::collisionCalc(float& step, float deltaTime, Entity& movingEntity, std::vector<Entity*>& stillEntities, std::vector<Entity*>& collidedEntities) {
	float threshold = 0.0001;
	
	collidedEntities.clear();
	
	bool anyCollision = false;
	float nearestStep = 1;
	for (int i = 0; i < stillEntities.size(); i++) {
		Entity* e = stillEntities[i];

		float currentStep = 1;

		if (!movingEntity.collisionCalc(currentStep, deltaTime, *e))
			continue;

		if (!anyCollision || currentStep < nearestStep - threshold) {
			anyCollision = true;
			nearestStep = currentStep;
			collidedEntities.clear();
			collidedEntities.push_back(e);
		}
		else if (abs(currentStep - nearestStep) < threshold) {
			collidedEntities.push_back(e);
		}
	}

	step = nearestStep;
	return anyCollision;
}

bool Collisions::collisionCalc(float& step, float deltaTime, Entity& movingEntity, std::vector<Entity*>& stillEntities) {
	std::vector<Entity*> dummy;
	return collisionCalc(step, deltaTime, movingEntity, stillEntities, dummy);
}

bool Collisions::collisionCalc(float& step, float deltaTime, Entity& movingEntity, Entity*** stillEntities, int cols, int rows, std::vector<Entity*>& collidedEntities) {
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
	int leftCol = fmax(int(floor(leftBound)), 0);
	int rightCol = fmin(int(floor(rightBound)), cols - 1);
	int topRow = fmax(int(floor(topBound)), 0);
	int bottomRow = fmin(int(floor(bottomBound)), rows - 1);

	//only search tiles within the calculated x and y range
	std::vector<Entity*> checkTiles;
	for (int x = leftCol; x <= rightCol; x++) {
		for (int y = topRow; y <= bottomRow; y++) {
			Entity* e = stillEntities[x][y];
			if (e != NULL)
				checkTiles.push_back(e);
		}
	}

	return collisionCalc(step, deltaTime, movingEntity, checkTiles, collidedEntities);
}

bool Collisions::collisionCalc(float& step, float deltaTime, Entity& movingEntity, Entity*** stillEntities, int cols, int rows) {
	std::vector<Entity*> dummy;
	return collisionCalc(step, deltaTime, movingEntity, stillEntities, cols, rows, dummy);
}