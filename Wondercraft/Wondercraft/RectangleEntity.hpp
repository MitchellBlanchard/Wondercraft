#pragma once

#include <SFML/Graphics.hpp>

class RectangleEntity : public sf::Transformable {
public:
	RectangleEntity(sf::Vector2f pos, sf::Vector2f dim);

protected:
	float left, top, right, bottom;

private:

};