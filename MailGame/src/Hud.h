#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Hud 
{

public:
	Hud();

	void render(RenderWindow * window);

private:
	Color mainColor;

	// accessory Colors
	Color ascryClrOne;
	Color ascryClrTwo;
};