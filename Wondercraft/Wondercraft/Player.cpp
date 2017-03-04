#include "Player.hpp"
#include <cmath>

Player::Player(sf::Vector2f spawn){
	float width = 1.5;
	float height = 2.5;
	rx = width / 2;
	ry = height / 2;

	setPosition(spawn);
}

void Player::updatePosition(float dt, TileType** tiles) {
	float dtRemaining = dt;

	while (dtRemaining > 0) {

		float xPortionExpended = 1;
		if (velocity.x < 0) {
			//check for all possible tile collisions along the left edge
			for (int xWall = floor(getPosition().x - rx); xWall > getPosition().x - rx + velocity.x; xWall--) {
				float xDiff = xWall - (getPosition().x - rx);
				float yDiff = velocity.y / velocity.x * xDiff;

				//check points along left edge
				int yPoint;
				for (yPoint = getPosition().y - ry + yDiff; yPoint <= getPosition().y + ry; yPoint++) {
					TileType& tile = tiles[int(yPoint)][xWall - 1];
					if (tile != TileType::NONE) {
						xPortionExpended = xDiff / velocity.x;
						break;
					}
				}
				//check bottom left corner if needed
				if (int(getPosition().y + ry) > int(yPoint)) {
					yPoint = getPosition().y + ry;

					TileType& tile = tiles[int(yPoint)][xWall - 1];
					if (tile != TileType::NONE) {
						xPortionExpended = xDiff / velocity.x;
						break;
					}
				}
			}
		}
		else if (velocity.x > 0) {
			//check for all possible tile collisions along the right edge
			for (int xWall = ceil(getPosition().x + rx); xWall < getPosition().x + rx + velocity.x; xWall++) {
				float xDiff = xWall - (getPosition().x + rx);
				float yDiff = velocity.y / velocity.x * xDiff;

				//check points along right edge
				int yPoint;
				for (yPoint = getPosition().y - ry + yDiff; yPoint <= getPosition().y + ry; yPoint++) {
					TileType& tile = tiles[int(yPoint)][xWall + 1];
					if (tile != TileType::NONE) {
						xPortionExpended = xDiff / velocity.x;
						break;
					}
				}
				//check bottom right corner if needed
				if (int(getPosition().y + ry) > int(yPoint)) {
					yPoint = getPosition().y + ry;

					TileType& tile = tiles[int(yPoint)][xWall + 1];
					if (tile != TileType::NONE) {
						xPortionExpended = xDiff / velocity.x;
						break;
					}
				}
			}
		}

		float yPortionExpended = 1;
		if (velocity.y < 0) {
			//check for all possible tile collisions along the top edge
			for (int yWall = floor(getPosition().y - ry); yWall > getPosition().x - rx + velocity.x; yWall--) {
				float yDiff = yWall - (getPosition().y - ry);
				float xDiff = velocity.x / velocity.y * yDiff;

				//check points along top edge
				int xPoint;
				for (xPoint = getPosition().x - rx + xDiff; xPoint <= getPosition().x + rx; xPoint++) {
					TileType& tile = tiles[yWall - 1][int(xPoint)];
					if (tile != TileType::NONE) {
						yPortionExpended = yDiff / velocity.y;
						break;
					}
				}
				//check top right corner if needed
				if (int(getPosition().x + rx) > int(xPoint)) {
					xPoint = getPosition().x + rx;

					TileType& tile = tiles[yWall - 1][int(xPoint)];
					if (tile != TileType::NONE) {
						yPortionExpended = yDiff / velocity.y;
						break;
					}
				}
			}
		}
		else if (velocity.y > 0) {
			//check for all possible tile collisions along the bottom edge
			for (int yWall = ceil(getPosition().y + ry); yWall < getPosition().y + ry + velocity.y; yWall++) {
				float yDiff = yWall - (getPosition().y + ry);
				float xDiff = velocity.x / velocity.y * yDiff;

				//check points along bottom edge
				int xPoint;
				for (xPoint = getPosition().x - rx + xDiff; xPoint <= getPosition().x + rx; xPoint++) {
					TileType& tile = tiles[yWall + 1][int(xPoint)];
					if (tile != TileType::NONE) {
						yPortionExpended = yDiff / velocity.y;
						break;
					}
				}
				//check bottom right corner if needed
				if (int(getPosition().x + rx) > int(xPoint)) {
					xPoint = getPosition().x + rx;

					TileType& tile = tiles[yWall + 1][int(xPoint)];
					if (tile != TileType::NONE) {
						yPortionExpended = yDiff / velocity.y;
						break;
					}
				}
			}
		}

		float dtElapsed;
		if (xPortionExpended == 1 && yPortionExpended == 1) {
			dtElapsed = dtRemaining;

			move(velocity.x * dtElapsed, velocity.y * dtElapsed);
		}
		else if (xPortionExpended == yPortionExpended) {
			dtElapsed = xPortionExpended * dtRemaining;

			move(velocity.x * dtElapsed, velocity.y * dtElapsed);
			velocity.x = 0;
			velocity.y = 0;
		}
		else if (xPortionExpended < yPortionExpended) {
			dtElapsed = xPortionExpended * dtRemaining;

			move(velocity.x * dtElapsed, velocity.y * dtElapsed);
			velocity.x = 0;
		}
		else if (yPortionExpended < xPortionExpended) {
			dtElapsed = yPortionExpended * dtRemaining;

			move(velocity.x * dtElapsed, velocity.y * dtElapsed);
			velocity.y = 0;
		}
		else {
			dtElapsed = dtRemaining;
		}

		dtRemaining -= dtElapsed;
	}
}