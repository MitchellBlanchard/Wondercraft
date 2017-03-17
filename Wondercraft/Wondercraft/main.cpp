#include "Game.hpp"
/*
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "RectangleEntity.hpp"
#include "Collisions.hpp"
#include <vector>
#include <iostream>
using namespace std;*/

int main() {
	/*
	Player a(sf::Vector2f(15, 15));
	a.setVelocity(sf::Vector2f(10, 11));
	RectangleEntity b(sf::Vector2f(17, 17), sf::Vector2f(1, 1));
	RectangleEntity c(sf::Vector2f(20, 17), sf::Vector2f(1, 1));

	vector<Entity*> vec;
	vec.push_back(&b);
	vec.push_back(&c);

	cout << "a (l,t,r,b):(" << a.getLeft() << ", " << a.getTop() << ", " << a.getRight() << ", " << a.getBottom() << ")" << endl;
	cout << "b (l,t,r,b):(" << b.getLeft() << ", " << b.getTop() << ", " << b.getRight() << ", " << b.getBottom() << ")" << endl;
	cout << "c (l,t,r,b):(" << c.getLeft() << ", " << c.getTop() << ", " << c.getRight() << ", " << c.getBottom() << ")" << endl;
	cout << endl;

	while (true);*/

	Game game;

	game.loop();

	return 0;
}