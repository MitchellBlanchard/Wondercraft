#include "Player.hpp"

#include "Collisions.hpp"
#include "Model.hpp"

Player::Player(sf::Vector2f position): RectangleEntity(position, sf::Vector2f(1.5, 2.5)) {}

void Player::update(float deltaTime, Model* model) {
	//initial step in the direction of the velocity
	float initialStep = Collisions::collisionCalc(deltaTime, *this, model->mapTiles, model->levelWidth, model->levelHeight);
	
	if (initialStep < 0) {
		//no collision, take full step
		position += velocity * deltaTime;
	}
	else {
		position += velocity * deltaTime * initialStep;

		float remainder = 1 - initialStep;

		//the collisions are limited to axis-aligned edges,
		//so try to take a second step in both the horizontal and vertical directions
		//and pick whichever one goes the furthest (at least one of them should always be 0)

		sf::Vector2f savedVelocity = velocity; // save velocity's current value for later

		velocity.y = 0;
		float hStep = Collisions::collisionCalc(deltaTime * remainder, *this, model->mapTiles, model->levelWidth, model->levelHeight);

		if (hStep < 0) {
			//no collision, assuming we collided with a top or bottom surface,
			//take horizontal step and keep velocity.y set to 0
			position += velocity * deltaTime * remainder;
		}
		else {
			velocity.y = savedVelocity.y; // reset velocity.y
			velocity.x = 0;
			float vStep = Collisions::collisionCalc(deltaTime * remainder, *this, model->mapTiles, model->levelWidth, model->levelHeight);
			
			if (vStep < 0) {
				//no collision, assuming we collided with a left or right surface,
				//take vertical step and keep velocity.x set to 0
				position += velocity * deltaTime * remainder;
			}
			else {
				//this should only happen if you are moving directly into an inside corner
				//(and possibly an outside corner, I'm not sure)
				//set velocity to (0, 0) and don't move
				velocity = sf::Vector2f(0, 0);
			}
		}
	}
}