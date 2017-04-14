#pragma once
#include "SFML/Graphics.hpp"

#include "Entity.h"

using namespace std;
using namespace sf;

class Building: public Entity
{
public:
	Building(Vector2i pos, Direction dir, string spritePath);
	virtual ~Building() {};

	virtual void update(Time dt) = 0;
	virtual void render(RenderWindow * window);

protected:
	Sprite * s;
};