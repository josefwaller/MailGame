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

	vector<UiButton> buttons;

	void render(RenderWindow * window);

private:

	// the app the HUD belongs to
	App * app;
};