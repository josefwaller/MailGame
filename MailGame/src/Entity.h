#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Entity
{
public:

	// an enum of the possible directions an entity can face
	enum Direction {
		Up,
		UpLeft,
		Left,
		DownLeft,
		Down,
		DownRight,
		Right,
		UpRight
	};

	Entity(Vector2f position, Entity::Direction dir);
	virtual ~Entity() {};

	// update must be initialized by the child class
	virtual void update(Time dt) = 0;

	// render must be initialized by the child class
	virtual void render(RenderWindow * r) = 0;

	Vector2f getPosition();

protected:
	// the position of the entity
	Vector2f position;

	// the direction the entity is facing
	Direction direction;
};