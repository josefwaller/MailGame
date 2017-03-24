#pragma once

#include "SFML/Graphics.hpp"
#include "UiButton.h"

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

	// a vector of the buttons
	vector<UiButton> buttons;

	// the UiElement of the top bar
	//UiElement topBar;
};