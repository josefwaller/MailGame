#pragma once
#include "SFML/Graphics.hpp"

#include "Entity.h"

using namespace std;
using namespace sf;

class Building: public Entity
{
public:
	Building(Vector2f pos, string spritePath);
	virtual ~Building() {};

	virtual void update(Time dt) = 0;
	virtual void render(RenderWindow * window);

private:
	Sprite * s;
};