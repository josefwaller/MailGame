#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

// Base class for all UiElements
class UiElement
{
public:

	static const int five = 5;

	// sets colors
	static const Color mainColor;

	static const Color colorOne;
	static const Color colorTwo;

	UiElement(int x, int y, int w, int h);

	virtual void onEvent(Event e) = 0;

	virtual void render(RenderWindow * window);


protected:
	int x;
	int y;
	int w;
	int h;

	void drawBorderedRect(FloatRect r, RenderWindow * window);
};