#pragma once
#include "NodeMap.h"

#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameMap
{
public:
	GameMap();
	void init(const int W, const int H, double density);
	void debugRender(sf::RenderWindow * window, int offX, int offY, int scale);

	void renderRoads(sf::RenderWindow * window, int scale);
	void renderHouses(sf::RenderWindow * window);

private:

	sf::Sprite * testSprite;
	sf::Sprite * roadSprite;

	void generateCity(int x, int y, int w, int h);
	sf::Sprite * loadTileSprite(string fPath);

	enum class terrain;

	// 2D array of terrain used for checking whether the player
	// can build stuff somewhere and for rendering
	std::vector<std::vector<terrain>> mapData;

	// nodemap of roads for pathfinding
	NodeMap roadMap;
};