#include "DrawableGroup.hpp"

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
	for (int i=0; i < drawList.size(); i++) {
		target.draw(*drawList[i], states.transform.combine(this->getTransform()));
	}
}