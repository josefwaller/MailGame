#pragma once

#include "GameMap.h"
#include "windows.h"

#include "Hud.h"

#include <SFML/Graphics.hpp>

class App
{
public:
	App(const int W, const int H, RenderWindow * gameWindow);

	// initializes the app
	void init();

	// updates the app
	void update(sf::Time dt);

	// renders the app
	void render(RenderWindow * window);
	
	// destroys the app
	void destroy();

	// scales the entities to an appropriate size
	static int getScale();

	// converts game coords into window coords
	static sf::Vector2f getRenderCoords(Vector2f worldCoords);

	// get and set methods
	int getW();
	int getH();

private:

	// the game map
	GameMap m;

	// the dimensions of the window
	int W;
	int H;

	// The HUD element
	// manages Heads Up Display
	Hud hud;

	// the width/height of the map
	static const int mapS = 50;

	// the window the game exists in
	RenderWindow * window;

	// how close the mouse can get to the edge of the screen without the screen panning
	const float mouseThreshold = 0.2f;

	// the speed at which the screen pans
	const int screenSpeed = 200;

	// the view of all game elements
	View gameView;

	// the debug view for drawing debugging information
	View debugView;

	// the hud view
	View hudView;
};