#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Map
{
public:
	Map();
	void init(const int W, const int H, double density);
	void debugRender(sf::RenderWindow * window, int offX, int offY, int scale);

private:
	enum class terrain;
	std::vector<std::vector<terrain>> mapData;
};