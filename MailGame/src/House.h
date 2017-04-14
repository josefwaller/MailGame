#pragma once
#include "SFML/Graphics.hpp"

#include "Building.h"

using namespace std;
using namespace sf;

class House : public Building
{
public:
	House(Vector2i pos, Direction dir);
	void update(Time dt);
	//void render(RenderWindow * window);

private:
	// variables used for timing letter generation
	long lastMailTime;
	static const long mailInterval = 200;
};