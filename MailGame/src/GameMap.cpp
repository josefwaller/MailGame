#include "GameMap.h"
#include "App.h"
#include "ResourceManager.h"

#include "windows.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <sstream>

using namespace std;
using namespace sf;

enum class GameMap::terrain 
{
	Empty,
	Road,
	House
};

GameMap::GameMap()
{
}

void GameMap::init(const int W, const int H, double density)
{
	srand((unsigned int)time(0));

	// starts map with 100 by 100
	mapData.assign(100, std::vector<terrain>(100, terrain::Empty));

	// initializes the nodemap
	roadMap = NodeMap();

	generateCity(11, 11, 10);
	//generateCity(40, 40, 21, 20);

	roadMap.addNodesAtIntersections();

	testSprite = loadTileSprite("assets/sprites/test_tile.png");
	roadSprite = loadTileSprite("assets/sprites/roads/road_base.png");

	updateMapGraphics();
}

void GameMap::generateCity(int cityX, int cityY, int startingRoadL)
{

	// NOTE TO SELF: These control what the map looks like
	const unsigned int MIN_LENGTH = 5;
	const unsigned int MAX_LENGTH = 20;
	const unsigned int NUM_OF_BRANCHES = 6;
	const unsigned int FRACTAL_LIMIT = 15;
	const unsigned  int MAX_OFFSET = 8;
	const unsigned int MIN_OFFSET = 0;

	// uses this temporary road struct when generating roads
	struct road {
		int x;
		int y;
		int l;
		bool isH;
	};

	// the list of accepted roads
	std::vector<road> roads = {};

	// the list of maybe acceptable roads
	std::vector<road> roadList = {};

	// the list of roads to check next time
	std::vector<road> tempRoads = {};

	// starts with 4 fours each going in a different direction
	for (int i = 0; i < 2; i++) {

		int x = 0;
		int y = 0;

		bool isH = i % 2 == 0;

		if (isH) {
			x = -startingRoadL;
		} 
		else {
			y = -startingRoadL;
		}

		roadList.push_back({
			x,
			y,
			2 * startingRoadL,
			isH
		});
	}

	// does 15 degrees of roads
	for (int i = 0; i < FRACTAL_LIMIT; i++) {

		for (road r : roadList) {

			// checks if that road is acceptable
			bool valid = true;

			// checks if it is in bounds
			if (cityX + r.x < 0 || cityX + r.x + r.l >(int) mapData.size()) {
				valid = false;
			}
			if (cityY + r.y < 0 || cityY + r.y + r.l >(int) mapData[0].size()) {
				valid = false;
			}

			// checks it is not beside any other roads and going in the same direction
			for (road rTwo : roads) {

				if (rTwo.isH == r.isH) {

					if (r.isH == true) {
						if (abs(r.y - rTwo.y) <= 1) {
							valid = false;
						}
					}
					else {
						if (abs(r.x - rTwo.x) <= 1) {
							valid = false;
						}
					}

				}

			}

			// if it's valid, adds it to the roads
			if (valid) {
				roads.push_back(r);

				// adds this road to the NodeMap
				int nOne = roadMap.addNode(Vector2i(cityX + r.x, cityY + r.y));

				int nTwo;
				if (r.isH) {
					nTwo = roadMap.addNode(Vector2i(cityX + r.x + r.l, cityY + r.y));
				}
				else {
					nTwo = roadMap.addNode(Vector2i(cityX + r.x, cityY + r.y + r.l));
				}

				roadMap.addConnection(nOne, nTwo);

				// generates new roads from this road
				for (int i = 0; i < NUM_OF_BRANCHES; i++) {

					int newLength = rand() % (MAX_LENGTH - MIN_LENGTH) + MIN_LENGTH;

					int randOffset = rand() % (MAX_OFFSET - MIN_OFFSET) + MIN_OFFSET;

					if (randOffset > newLength) {
						randOffset = newLength;
					}

					if (r.isH) {

						tempRoads.push_back({ r.x + rand() % r.l, r.y - randOffset, newLength, false });

					}
					else {

						tempRoads.push_back({ r.x - randOffset, r.y + rand() % r.l, newLength, true });

					}

				}

			} // if

		} // for

		roadList = tempRoads;

	}

	for (road r : roads) {

		for (int i = 0; i < r.l; i++) {
			if (r.isH) {
				mapData[cityX + r.x + i][cityY + r.y] = terrain::Road;
			}
			else {
				mapData[cityX + r.x][cityY + r.y + i] = terrain::Road;
			}
		}
	}

}

sf::Sprite GameMap::loadTileSprite(string fPath)
{
	sf::Sprite sprite = sf::Sprite(*ResourceManager::get()->loadSprite(fPath));

	// sets the origin to center so they can be easily drawn
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	sprite.setOrigin(0.5 * spriteBounds.width, 0.5 * spriteBounds.height);

	Vector2f origin = App::getRenderCoords(Vector2f(0, 0));
	Vector2f end = App::getRenderCoords(Vector2f(1, 1));

	float scale = (end.y - origin.y) * App::getScale() / spriteBounds.height;
	sprite.setScale(scale, scale);

	return sprite;
}

void GameMap::debugRender(sf::RenderWindow * window, int offX, int offY, int scale)
{

	for (size_t i = 0; i < roadMap.getConnections().size(); i++) {
		
		Vector2i nodeOne = roadMap.getNode(roadMap.getConnections()[i].first);
		Vector2i nodeTwo = roadMap.getNode(roadMap.getConnections()[i].second);

		nodeOne.x *= scale;
		nodeTwo.x *= scale;
		nodeOne.y *= scale;
		nodeTwo.y *= scale;

		sf::Vertex line[] = {
			sf::Vertex((sf::Vector2f)nodeOne),
			sf::Vertex((sf::Vector2f)nodeTwo)
		};

		window->draw(line, 2, sf::Lines);

	}

	for (size_t i = 0; i < roadMap.getNodes().size(); i++) {

		Vector2i node = roadMap.getNode((int)i);

		sf::CircleShape circ((float) (scale * 0.5));
		circ.setPosition((float)((node.x - 0.5) * scale), (float)((node.y - 0.5) * scale));
		circ.setFillColor(sf::Color(255, 0, 0, 200));

		window->draw(circ);

	}

}

void GameMap::updateMapGraphics()
{

	int scale = App::getScale();

	sf::RenderTexture text;

	// gets the dimensions
	int textureW = App::getRenderCoords(Vector2f(mapData.size(), 0)).x - App::getRenderCoords(Vector2f(0, mapData.size())).x;
	int textureH = App::getRenderCoords(Vector2f(mapData.size(), mapData[0].size())).y - App::getRenderCoords(Vector2f(0, 0)).y;

	if (!text.create(scale * textureW, scale * textureH)) {

	}

	float xOffset = textureW / 2 * scale;

	for (size_t x = 0; x < mapData.size(); x++) {
		for (size_t y = 0; y < mapData[x].size(); y++) {

			// gets the middle point
			Vector2f middle = App::getRenderCoords(Vector2f(
				(x + 0.5) * scale,
				(y + 0.5) * scale
			));

			middle.x += xOffset;

			// draws the background spritre
			testSprite.setPosition(middle);
			text.draw(testSprite);

			// draws the sprite
			sf::Sprite sprite;

			if (mapData[x][y] == terrain::Road) {
				sprite = roadSprite;
				sprite.setPosition(middle);
				text.draw(sprite);
			}

			// creates a new rectangle
			sf::RectangleShape middlePoint(sf::Vector2f(1, 1));
			middlePoint.setFillColor(sf::Color::Red);

			// sets the rect's position
			middlePoint.setPosition(middle);

			// draws the point
			text.draw(middlePoint);

		}
	}

	// draws a debug grid
	for (size_t x = 0; x < mapData.size(); x++) {

		// gets the coordinates
		Vector2f origin = App::getRenderCoords(Vector2f((float)(x * scale), 0));
		Vector2f endPoint = App::getRenderCoords(Vector2f((float)(x * scale), (float)(mapData[0].size() * scale)));

		origin.x += xOffset;
		endPoint.x += xOffset;

		sf::Vertex line[] = {
			sf::Vertex(origin),
			sf::Vertex(endPoint)
		};

		// draws the line
		text.draw(line, 2, sf::Lines);
	}

	for (int y = 0; y < mapData[0].size(); y++) {

		Vector2f origin = App::getRenderCoords(Vector2f(0, y * scale));
		Vector2f endPoint = App::getRenderCoords(Vector2f(mapData[0].size() * scale, y * scale));

		origin.x += xOffset;
		endPoint.x += xOffset;

		sf::Vertex line[] = {
			sf::Vertex(origin),
			sf::Vertex(endPoint)
		};

		text.draw(line, 2, sf::Lines);

	}

	mapTexture = text.getTexture();
}

void GameMap::renderRoads(sf::RenderWindow * window, int scale)
{

	Sprite s(mapTexture);
	window->draw(s);
}