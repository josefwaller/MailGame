#pragma once

#include "GameMap.h"

#include <SFML/Graphics.hpp>

class App
{
public:
	App();
	void init();
	void update();
	void render(sf::RenderWindow * window);
	void destroy();

private:
	GameMap m;
	int y;
};