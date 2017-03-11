#pragma once

#include "Entity.h"

Entity::Entity(Vector2f startingPos, Direction dir)
{
	position = startingPos;
	direction = dir;
}

Vector2f Entity::getPosition()
{
	return position;
}