#pragma once

#include <SFGUI/Widgets.hpp>

#include "SFML/Graphics.hpp"

// forward declaration of App
class App;

using namespace std;
using namespace sf;

class Hud 
{

public:
	Hud();
	Hud(App * app, sfg::Desktop * d);

	sfg::Window::Ptr toolbar;

	void render(RenderWindow * window);

private:

	// the app the HUD belongs to
	App * app;
};