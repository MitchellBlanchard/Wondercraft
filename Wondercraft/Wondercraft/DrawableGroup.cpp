#include "DrawableGroup.hpp"

DrawableGroup::DrawableGroup(const sf::Transformable& t) {
	setWrappedObject(t);
}

void DrawableGroup::setWrappedObject(const sf::Transformable& t) {
	wrappedObject = &t;
}

const sf::Transformable& DrawableGroup::getWrappedObject() {
	return *wrappedObject;
}

bool DrawableGroup::contains(const Drawable& u) {
	for (std::vector<Drawable*>::iterator it = drawList.begin(); it < drawList.end(); it++) {
		if (*it == &u) {
			return true;
			break;
		}
	}
	return false;
}

void DrawableGroup::add(Drawable& u) {
	drawList.push_back(&u);
}

void DrawableGroup::remove(const Drawable& u) {
	for (std::vector<Drawable*>::iterator it = drawList.begin(); it < drawList.end(); it++) {
		if (*it == &u) {
			drawList.erase(it);
			break;
		}
	}
}

void DrawableGroup::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= wrappedObject->getTransform();
	for (int i=0; i < drawList.size(); i++) {
		target.draw(*drawList[i], states);
	}
}