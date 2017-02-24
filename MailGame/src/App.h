#pragma once

#include "GameMap.h"
#include "windows.h"

#include <SFML/Graphics.hpp>

class App
{
public:
	App(const int W, const int H);
	void init();
	void update();
	void render(sf::RenderWindow * window);
	void destroy();

	static sf::Vector2f getRenderCoords(sf::Vector2f worldCoords);

	// used for logging

	template<class T>
	static void logToConsole(T val, std::string before = "", std::string after = "")
	{
		std::ostringstream os;
		os << before << val << after << std::endl;
		OutputDebugStringA(os.str().c_str());
	}

private:
	GameMap m;

	// the view of all game elements
	sf::View gameView;

	// the hud view
	sf::View hudView;
};