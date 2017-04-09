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
};