#pragma once

#include <vector>

#include "Entity.hpp"

namespace Collisions {

	//returns the fraction of the frame step until the moving entity collides with any of the given still entities
	//returns a negative value if there is no collision
	//fills an empty vector, collidedEntities, with any of the stillEntities that have a collision value equal to the value returned
	float collisionCalc(float deltaTime, Entity& movingEntity, std::vector<Entity*>& stillEntities, std::vector<Entity*>& collidedEntities);

	//return value only, does not output list of collided entities
	float collisionCalc(float deltaTime, Entity& movingEntity, std::vector<Entity*>& stillEntities);

	//stillEntities is a 2D array rather than a vector
	float collisionCalc(float deltaTime, Entity& movingEntity, Entity*** stillEntities, int cols, int rows, std::vector<Entity*>& collidedEntities);

	//return value only, does not output list of collided entities
	float collisionCalc(float deltaTime, Entity& movingEntity, Entity*** stillEntities, int cols, int rows);
}