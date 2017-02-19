#pragma once

#include "Map.h"

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
	Map m;
	int y;
};