#include "UpdateableGroup.hpp"

bool UpdateableGroup::contains(const Updateable& u) {
	for (std::vector<Updateable*>::iterator it = updateList.begin(); it < updateList.end(); it++) {
		if (*it == &u) {
			return true;
			break;
		}
	}
	return false;
}

void UpdateableGroup::add(Updateable& u) {
	updateList.push_back(&u);
}

void UpdateableGroup::remove(const Updateable& u) {
	for (std::vector<Updateable*>::iterator it = updateList.begin(); it < updateList.end(); it++) {
		if (*it == &u) {
			updateList.erase(it);
			break;
		}
	}
}

void UpdateableGroup::update(float dt) {
	for (int i = 0; i < updateList.size(); i++) {
		updateList[i]->update(dt);
	}
}