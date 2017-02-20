#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class DrawableGroup : public sf::Drawable {
public:
	DrawableGroup(const sf::Transformable&);

	void setWrappedObject(const sf::Transformable&);
	const sf::Transformable& getWrappedObject();

	bool contains(const sf::Drawable&);
	void add(sf::Drawable&);
	void remove(const sf::Drawable&);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	const sf::Transformable* wrappedObject;
	std::vector<sf::Drawable*> drawList;
};