#pragma once
#include "SFML/Graphics.hpp"

#include "Entity.h"

using namespace sf;

class Building: public Entity
{
public:
	Building(Vector2f pos);
	virtual ~Building() {};

private:

};