#pragma once

class Updateable {
public:
	virtual void update(float deltaTime) = 0;
};