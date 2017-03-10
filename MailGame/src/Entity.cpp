#pragma once

#include "Entity.h"

Entity::Entity(Vector2f startingPos)
{
	position = startingPos;
}

Vector2f Entity::getPosition()
{
	return position;
}

enum Entity::direction {
	Up,
	UpLeft,
	Left,
	DownLeft,
	Down,
	DownRight,
	Right,
	UpRight
};