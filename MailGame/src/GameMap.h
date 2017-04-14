#pragma once
#include "NodeMap.h"
#include "Building.h"

#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameMap
{
public:
	GameMap();
	void init(const int W, const int H, int mapSize);
	void destroy();

	void updateBuildings(Time dt);
	void debugRender(sf::RenderWindow * window, FloatRect clipRect);

	void renderRoads(sf::RenderWindow * window, FloatRect clipRect);
	void renderBuildings(sf::RenderWindow * window, FloatRect clipRect);

private:

	// vector of buildings on the map
	vector<Building *> buildings;

	sf::Sprite testSprite;
	sf::Sprite roadSprites[5];

	void generateCity(int x, int y, int l);
	sf::Sprite loadTileSprite(string fPath);

	enum class terrain;

	// 2D array of terrain used for checking whether the player
	// can build stuff somewhere and for rendering
	std::vector<std::vector<terrain>> mapData;

	// nodemap of roads for pathfinding
	NodeMap roadMap;
};