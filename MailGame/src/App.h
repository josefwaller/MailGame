#pragma once

#include "GameMap.h"

#include <SFML/Graphics.hpp>

class App
{
public:
	App(const int W, const int H);
	void init();
	void update();
	void render(sf::RenderWindow * window);
	void destroy();

	std::pair<int, int> getRenderCoords(std::pair<int, int> worldCoords);

private:
	GameMap m;

	// the view of all game elements
	sf::View gameView;

	// the hud view
	sf::View hudView;
};