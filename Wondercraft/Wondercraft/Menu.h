#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
public:
	Menu();
	sf::Vector2f selectedLoc; //woah look at the blank ass class nyahahahhh
	int menuSide; //1: equipment, 2: crafting, 3: inventory
	int x, y; //some shit don worry
};
#endif
