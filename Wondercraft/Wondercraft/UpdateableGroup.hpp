#pragma once

#include <vector>
#include "Updateable.hpp"

class UpdateableGroup : public Updateable {
public:
	bool contains(Updateable*);
	void add(Updateable*);
	void remove(Updateable*);

	void update(float deltaTime);

private:
	std::vector<Updateable*> updateList;
};