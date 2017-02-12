#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class DrawableGroup : public sf::Drawable, public virtual sf::Transformable {
public:
	bool contains(const sf::Drawable&);
	void add(sf::Drawable&);
	void remove(const sf::Drawable&);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	std::vector<sf::Drawable*> drawList;
};