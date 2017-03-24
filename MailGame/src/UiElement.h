#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

// Base class for all UiElements
class UiElement
{
public:

	UiElement(int x, int y, int w, int h);

	virtual void onEvent(Event e) = 0;

	virtual void render(RenderWindow * window) = 0;


protected:
	int x;
	int y;
	int w;
	int h;
};