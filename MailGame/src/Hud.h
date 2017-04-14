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

	void update();
	void render(RenderWindow * window);

	void onMenuSelect(vector<String> vals);

private:

	// the app the HUD belongs to
	App * app;

	// A map of the strings used in the menu
	// the key is what the string represents (File, build, etc)
	// and should not change, while the value is the actual
	// string drawn on the screen and can change
	// Read from a json file
	map<string, string> menuStrings;

	// whether the player is building something
	bool isBuilding;
};