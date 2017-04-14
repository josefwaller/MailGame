#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

// forward declaration of App
class App;

using namespace std;
using namespace sf;

class Hud 
{

public:
	Hud();
	Hud(App * app);

	// the theme for HUD things
	tgui::Theme::Ptr theme;

	// the toolbar of stuff to do
	tgui::MenuBar::Ptr toolbar;

	void init();

	void onMenuSelect(vector<String> vals);

	void render(RenderWindow * window);

private:

	// the app the HUD belongs to
	App * app;

	bool isCorrect;
};