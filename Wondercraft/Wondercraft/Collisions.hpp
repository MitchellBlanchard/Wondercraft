#pragma once

#include <vector>

#include "Entity.hpp"

// Contains functions for determining the nearest collision between a moving entity and a collection of still entities.
// A 'still' entity may have a velocity, but for the purpose of the calculation, it will not be used.
namespace Collisions {
	//Outputs into 'step' the fraction of the frame step until the moving entity collides with any of the given still entities,
	//or outputs 1.0f if there is no collision.
	//Returns whether or not there is a collision.
	//fills an empty vector, collidedEntities, with any of the stillEntities that have a collision value equal to the value returned
	bool collisionCalc(float& step, float deltaTime, Entity& movingEntity, std::vector<Entity*>& stillEntities, std::vector<Entity*>& collidedEntities);

	//does not output list of collided entities
	bool collisionCalc(float& step, float deltaTime, Entity& movingEntity, std::vector<Entity*>& stillEntities);

	//stillEntities is a 2D array rather than a vector
	bool collisionCalc(float& step, float deltaTime, Entity& movingEntity, Entity*** stillEntities, int cols, int rows, std::vector<Entity*>& collidedEntities);

	//does not output list of collided entities
	bool collisionCalc(float& step, float deltaTime, Entity& movingEntity, Entity*** stillEntities, int cols, int rows);
}