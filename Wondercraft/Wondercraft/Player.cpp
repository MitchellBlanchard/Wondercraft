#include "Player.hpp"

#include <cmath>

#include "Collisions.hpp"
#include "Model.hpp"

#include <iostream>
using namespace std;

Player::Player(sf::Vector2f position): RectangleEntity(position, sf::Vector2f(1.5, 2.5)) {
	projectileTimer = 0;
	facingRight = true;

	hat = ItemType::BASIC_HAT;
	robe = ItemType::BASIC_ROBE;
	staff = ItemType::BASIC_STAFF;
}

void Player::update(float deltaTime, Model* model) {
	if (projectileTimer != 0) {
		projectileTimer -= deltaTime;
	}

	if (projectileTimer <= 0) {
		projectileTimer = 0;
	}


	float threshold = 0.0001;

	cout << "bounds: " << getLeft() << ", " << getTop() << ", " << getRight() << ", " << getBottom() << endl;
	cout << "move: " << getVelocity().x * deltaTime << ", " << getVelocity().y * deltaTime << endl << endl;
	//initial step in the direction of the velocity
	float initialStep = 1;
	bool initialCollision = Collisions::collisionCalc(initialStep, deltaTime, *this, model->mapTiles, model->levelWidth, model->levelHeight);
	setPosition(getPosition() + velocity * deltaTime * initialStep);

	cout << "initial collision: " << initialCollision << endl;
	cout << "initial step: " << initialStep << endl << endl;

	if (initialCollision) {
		float remainder = 1 - initialStep;

		cout << "bounds: " << getLeft() << ", " << getTop() << ", " << getRight() << ", " << getBottom() << endl << endl;

		//the collisions are limited to axis-aligned edges,
		//so try to take a second step in both the horizontal and vertical directions
		//and pick whichever one goes the furthest (at least one of them should always be 0)

		sf::Vector2f savedVelocity = velocity; // save velocity's current value for later

		setVelocity(sf::Vector2f(savedVelocity.x, 0));
		float hStep = 1;
		bool hCollision = Collisions::collisionCalc(hStep, deltaTime * remainder, *this, model->mapTiles, model->levelWidth, model->levelHeight);
		cout << "horizontal move: " << getVelocity().x * deltaTime * remainder << ", " << getVelocity().y * deltaTime * remainder << endl;
		cout << "horizontal collision: " << hCollision << endl;
		cout << "horizontal step: " << hStep << endl << endl;

		if (!hCollision && abs(getVelocity().x) > threshold) {
			//no collision with a left or right surface, assume we collided with a top or bottom surface,
			//take horizontal step and keep velocity.y set to 0
			setPosition(getPosition() + velocity * deltaTime * remainder);
		}
		else {
			setVelocity(sf::Vector2f(0, savedVelocity.y));
			float vStep = 1;
			bool vCollision = Collisions::collisionCalc(vStep, deltaTime * remainder, *this, model->mapTiles, model->levelWidth, model->levelHeight);
			
			cout << "vertical move: " << getVelocity().x * deltaTime * remainder << ", " << getVelocity().y * deltaTime * remainder << endl;
			cout << "vertical collision: " << vCollision << endl;
			cout << "vertical step: " << vStep << endl << endl;

			if (!vCollision) {
				//no collision with a top or bottom surface, assume we collided with a left or right surface,
				//take vertical step and keep velocity.x set to 0
				setPosition(getPosition() + velocity * deltaTime * remainder);
			}
			else {
				//this should only happen if you are moving directly into an inside corner
				//(and possibly an outside corner, I'm not sure)
				//set velocity to (0, 0) and don't move
				setVelocity(sf::Vector2f(0, 0));
			}
		}
	}
}