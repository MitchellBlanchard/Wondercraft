#pragma once

#include <vector>
#include "Updateable.hpp"

class UpdateableGroup : public Updateable {
public:
	bool contains(const Updateable&);
	void add(Updateable&);
	void remove(const Updateable&);

	void update(float deltaTime);

private:
	std::vector<Updateable*> updateList;
};