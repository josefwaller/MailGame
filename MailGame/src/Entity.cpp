#pragma once

#include "Entity.h"
#include "App.h"

Entity::Entity(App * app, Vector2f startingPos, Direction dir)
{
	position = startingPos;
	direction = dir;
}

Vector2f Entity::getPosition()
{
	return position;
}