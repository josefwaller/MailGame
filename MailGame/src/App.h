#pragma once

#include "GameMap.h"
#include "windows.h"

#include "Hud.h"

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class App
{
public:
	App(const int W, const int H, RenderWindow * gameWindow, tgui::Gui * gui);

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

	/*
	 Coordinate Explination

	 There are 3 coordinate systems in place

	 1. The window coords, where each image is actually drawn on the window
	 2. The world coords, where each object is in the actual game world
	 3. The isometric coords, where each object is in the isometric view

	 The isometric coords are the same as the world coord, but rotated ~40*
	 and squished.
	 */

	// converts game coords into isometric coords
	static Vector2f getRenderCoords(Vector2f worldCoords);

	// converts isometric coords into game coords
	// basically will undo getRenderCoords
	static Vector2f getGameCoordsFromRenderCoords(Vector2f renderCoords);

	// converts window coords into game coords
	Vector2f getGameCoordsFromScreen(Vector2i windowCoords);

	// get and set methods
	int getW();
	int getH();
	RenderWindow * getWindow();
	GameMap * getGameMap();

	tgui::Gui * getGui();

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

	// The GUI for the game
	tgui::Gui * gui;

	// the speed at which the screen pans
	const int screenSpeed = 200;

	// the view of all game elements
	View gameView;

	// the debug view for drawing debugging information
	View debugView;

	// the hud view
	View hudView;

	// moves the view when the mouse is at the edges
	void moveView(Time dt);
};