#include "Game.hpp"

/*#include <SFML/Graphics.hpp>
#include "LeftEdgeEntity.hpp"
#include "RightEdgeEntity.hpp"
#include <iostream>
using namespace std;*/

int main() {
	/*LeftEdgeEntity a(sf::Vector2f(10, 0), 10);
	a.velocity = sf::Vector2f(-11, 11);
	RightEdgeEntity b(sf::Vector2f(0, 0), 10);
	cout << a.checkAABB(b) << " " << a.checkMovingAABB(1, b) << " " << a.collisionCalc(1, b) << endl;

	a.position = sf::Vector2f(10, 10);
	a.velocity = sf::Vector2f(-10, 1);
	cout << a.checkAABB(b) << " " << a.checkMovingAABB(1, b) << " " << a.collisionCalc(1, b) << endl;

	while (true);*/

	Game game;

	game.loop();

	return 0;
}