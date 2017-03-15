#pragma once

#include "GameMap.h"
#include "windows.h"

#include "Hud.h"

#include <SFML/Graphics.hpp>

class App
{
public:
	App(const int W, const int H, sf::RenderWindow * gameWindow);
	void init();
	void update();
	void render(sf::RenderWindow * window);
	void destroy();

	static int getScale();

	static sf::Vector2f getRenderCoords(sf::Vector2f worldCoords);

	// get and set methods
	int getW();
	int getH();

	// used for logging

	template<class T>
	static void logToConsole(T val, std::string before = "", std::string after = "")
	{
		std::ostringstream os;
		os << before << val << after << std::endl;
		OutputDebugStringA(os.str().c_str());
	}

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