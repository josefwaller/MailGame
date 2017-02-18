#pragma once

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
	int y;
};