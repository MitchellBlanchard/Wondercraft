#pragma once

#include "UpdateableGroup.hpp"
#include "DrawableGroup.hpp"

class Model : public UpdateableGroup, public DrawableGroup {
public:
	Model();

	void update(float deltaTime);

private:
	
};