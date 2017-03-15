#include <SFML/Graphics.hpp>

class Entity {
public:
	Entity(sf::Vector2f& spawn);

	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f velocity;

	//returns the fraction of the frame step until colliding with the given obejct
	//returns a negative value if there is no collision
	float collisionCalc(float deltaTime, Entity&);

	float getLeft();
	float getTop();
	float getRight();
	float getBottom();
private:

};