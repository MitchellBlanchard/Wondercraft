#include "Game.hpp"

/*
#include <SFML/Graphics.hpp>
#include "LeftEdgeEntity.hpp"
#include "RightEdgeEntity.hpp"
#include "TopEdgeEntity.hpp"
#include "BottomEdgeEntity.hpp"
#include "RectangleEntity.hpp"
#include <iostream>
using namespace std;*/

int main() {
	/*RectangleEntity a(sf::Vector2f(0, 0), sf::Vector2f(20, 10));
	a.setVelocity(sf::Vector2f(10, 30));
	RectangleEntity b(sf::Vector2f(20, 17.5), sf::Vector2f(5, 2));
	b.setVelocity(sf::Vector2f(-10, -30));

	cout << "a (l,t,r,b):(" << a.getLeft() << ", " << a.getTop() << ", " << a.getRight() << ", " << a.getBottom() << ")" << endl;
	cout << "a size: " << a.getSize().x << ", " << a.getSize().y << endl;
	cout << "b (l,t,r,b):(" << b.getLeft() << ", " << b.getTop() << ", " << b.getRight() << ", " << b.getBottom() << ")" << endl;
	cout << "b size: " << b.getSize().x << ", " << b.getSize().y << endl;
	cout << a.checkAABB(b) << " " << a.checkMovingAABB(1, b) << " " << a.collisionCalc(1, b) << endl;
	cout << b.checkAABB(a) << " " << b.checkMovingAABB(1, a) << " " << b.collisionCalc(1, a) << endl;

	while (true);*/

	Game game;

	game.loop();

	return 0;
}