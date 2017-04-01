#pragma once

#include "Model.hpp"
#include "View.hpp"

// Part of the Model-View-Controller architecture.
// Acts on the model and monitors the view for some input.
class Controller {
public:
	Controller(Model*, View*);

	//Acts on the Model based on inputs from the keyboard, mouse, etc.
	void inputs();

	//Returns whether the program ought to be running.
	//A return value of false means the program should exit by the next iteration of the game loop.
	bool isRunning() const;

private:
	Model* model;
	View* view;
};