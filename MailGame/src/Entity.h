#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Entity
{
public:
	Entity(Vector2f position);
	virtual ~Entity() {};

	// update must be initialized by the child class
	virtual void update(Time dt) = 0;

	// render must be initialized by the child class
	virtual void render(RenderWindow * r) = 0;

	Vector2f getPosition();

private:
	Vector2f position;
};