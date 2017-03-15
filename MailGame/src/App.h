#pragma once

#include "GameMap.h"
#include "windows.h"

#include "Hud.h"

#include <SFML/Graphics.hpp>

class App
{
public:
	App(const int W, const int H, sf::RenderWindow * gameWindow);

	// initializes the app
	void init();

	// updates the app
	void update();

	// renders the app
	void render(sf::RenderWindow * window);
	
	// destroys the app
	void destroy();

	// scales the entities to an appropriate size
	static int getScale();

	// converts game coords into window coords
	static sf::Vector2f getRenderCoords(sf::Vector2f worldCoords);

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
	sf::RenderWindow * window;

	// clock used for recording deltaTime
	sf::Clock deltaClock;

	// how close the mouse can get to the edge of the screen without the screen panning
	const float mouseThreshold = 0.2f;

	// the speed at which the screen pans
	const int screenSpeed = 200;

	// the view of all game elements
	sf::View gameView;

	// the hud view
	sf::View hudView;
};