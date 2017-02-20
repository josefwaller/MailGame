#pragma once
#include "NodeMap.h"

#include <vector>
#include <SFML/Graphics.hpp>

class GameMap
{
public:
	GameMap();
	void init(const int W, const int H, double density);
	void debugRender(sf::RenderWindow * window, int offX, int offY, int scale);

	void renderRoads(sf::RenderWindow * window);
	void renderHouses(sf::RenderWindow * window);

private:
	enum class terrain;
	std::vector<std::vector<terrain>> mapData;

	// nodemap of roads for pathfinding
	NodeMap roadMap;
};