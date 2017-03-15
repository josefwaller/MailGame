#pragma once

#include "SFML/Graphics.hpp"

// forward declaration of App
class App;

using namespace std;
using namespace sf;

class Hud 
{

public:
	Hud();
	Hud(App * app);

	void render(RenderWindow * window);

private:

	// the app the HUD belongs to
	App * app;

	Color mainColor;

	// accessory Colors
	Color ascryClrOne;
	Color ascryClrTwo;

	void drawBorderedRect(RenderWindow * window, FloatRect r);
};