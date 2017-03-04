#pragma once

#include <SFML/Graphics.hpp>

enum GeometryType {
	BOX,
	CIRCLE,
	POINT,
	H_LINE,
	V_LINE
};

class Entity : public sf::Transformable {
public:
	void move(std::vector<Entity>);

protected:
	float rx, ry;
	GeometryType geometryType;


private:

};

class RectangleEntity : public Entity {
public:
	RectangleEntity(sf::Vector2f pos, sf::Vector2f dim);

private:

};