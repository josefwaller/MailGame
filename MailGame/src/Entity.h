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

	// an enum of the possible directions an entity can face
	static enum direction;

	Vector2f getPosition();

protected:
	Vector2f position;
};