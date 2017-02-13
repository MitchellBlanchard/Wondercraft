#pragma once

#include "Model.hpp"
#include "View.hpp"

class Controller {
public:
	Controller(Model*, View*);

	void inputs();
	bool isRunning() const;

private:
	Model* model;
	View* view;
};