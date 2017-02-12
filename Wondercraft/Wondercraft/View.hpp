#pragma once

#include "Model.hpp"

class View {
public:
	View(const Model*);

	void render();

private:
	const Model* model;
};