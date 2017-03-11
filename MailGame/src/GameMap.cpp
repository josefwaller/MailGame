#include "GameMap.h"
#include "App.h"
#include "ResourceManager.h"
#include "House.h"

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

void GameMap::init(const int W, const int H, int mapSize)
{
	srand((unsigned int)time(0));

	// starts map with 100 by 100
	mapData.assign(mapSize, std::vector<terrain>(mapSize, terrain::Empty));

	// initializes the nodemap
	roadMap = NodeMap();

	// initializes buildings
	buildings = {};

	generateCity(11, 11, 10);

	string path = "assets/sprites/";

	testSprite = loadTileSprite(path + "tile.png");

	string roadSpriteNames[5] = {
		"base",
		"top",
		"left",
		"bot",
		"right"
	};

	for (int i = 0; i < 5; i++) {
		roadSprites[i] = loadTileSprite("assets/sprites/roads/road_" + roadSpriteNames[i] + ".png");
	}

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

	// adds the roads to mapData
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

	// adds nodes where two connections cross
	roadMap.addNodesAtIntersections();

	for (pair<int, int> connection : roadMap.getConnections()) {

		// gets the two nodes
		Vector2i nodeOne = roadMap.getNode(connection.first);
		Vector2i nodeTwo = roadMap.getNode(connection.second);

		// gets the range of x and y values that the road takes up
		pair<int, int> xRange;
		pair<int, int> yRange;

		if (nodeOne.x == nodeTwo.x) {

			// since these are the same, xRange will look like {x, x}
			xRange = { nodeOne.x, nodeTwo.x };
			
			// sets the smaller y value to the first pair value
			if (nodeOne.y > nodeTwo.y) {
				yRange = { nodeTwo.y, nodeOne.y - 1};
			}
			else {
				yRange = { nodeOne.y, nodeTwo.y - 1};
			}
		}
		// does the same for vertical roads
		else if (nodeOne.y == nodeTwo.y) {
			yRange = { nodeOne.y, nodeTwo.y};

			if (nodeOne.x > nodeTwo.x) {
				xRange = { nodeTwo.x, nodeOne.x - 1};
			}
			else {
				xRange = { nodeOne.x, nodeTwo.x - 1};
			}

		}

		// cycles through each road's tiles
		for (int x = xRange.first; x <= xRange.second; x++) {
			for (int y = yRange.first; y <= yRange.second; y++) {

				// sets an offset so that the houses are not on the road
				for (int xOff = -1; xOff <= 1; xOff++) {
					for (int yOff = -1; yOff <= 1; yOff++) {

						// since the houses cannot be diagonally attached to the road,
						// we can only place a house where only one offset is 0
						if ((xOff == 0 || yOff == 0) && xOff != yOff) {

							// checks the position is not off the map
							if (mapData.size() < x + xOff || mapData[0].size() < y + yOff) {
								continue;
							}

							// checks the terrain is empty
							if (mapData[x + xOff][y + yOff] == terrain::Empty) {

								Entity::Direction hDir;

								if (xOff == 0) {
									if (yOff == 1) {
										hDir = Entity::Direction::Up;
									}
									else {
										hDir = Entity::Direction::Down;
									}

								}
								else {
									if (xOff == 1) {
										hDir = Entity::Direction::Right;
									}
									else {
										hDir = Entity::Direction::Left;
									}
								}

								// places a house
								buildings.push_back(new House(Vector2f((float)(x + xOff), (float)(y + yOff)), hDir));

								// sets the terrain so that nothing else is build here
								mapData[x + xOff][y + yOff] = terrain::House;

							}

						}

					}
				}

			}
		}

	}
}

void GameMap::destroy()
{
	for (auto b : buildings) {
		delete b;
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

	float scale = (end.y - origin.y) / spriteBounds.height;
	sprite.setScale(scale, scale);

	return sprite;
}

void GameMap::debugRender(sf::RenderWindow * window, int offX, int offY)
{

	int scale = App::getScale();

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

	//mapTexture = text.getTexture();
}

void GameMap::renderRoads(sf::RenderWindow * window, FloatRect clipRect)
{

	int scale = App::getScale();

	// fills it initially with a green color to cover any holes

	// the color to fill it with
	Color green(4, 53, 0);

	// the size of each length
	float l = (float)(mapData.size());

	// the Vertex array to draw
	Vertex cover[4] = {
		Vertex(App::getRenderCoords({ 0, 0 }), green),
		Vertex(App::getRenderCoords({ 0, l }), green),
		Vertex(App::getRenderCoords({ l, l }), green),
		Vertex(App::getRenderCoords({ l, 0 }), green)
	};

	// draws the vertex array
	window->draw(cover, 4, Quads);

	float xOffset = 0;

	for (size_t x = 0; x < mapData.size(); x++) {
		for (size_t y = 0; y < mapData[x].size(); y++) {

			// gets the middle point
			Vector2f middle = App::getRenderCoords(Vector2f(
				(x + 0.5),
				(y + 0.5)
			));

			middle.x += xOffset;

			if (!clipRect.contains(middle.x, middle.y)) {
				continue;
			}

			// draws the background sprite
			testSprite.setPosition(middle);
			window->draw(testSprite);

			// draws a road if there needs to be one
			if (mapData[x][y] == terrain::Road) {

				// a vector of the road sprites which need to be drawn
				vector<Sprite> spritesToDraw;

				// adds the base sprite
				spritesToDraw.push_back(roadSprites[0]);

				if (y > 0 && mapData[x][y - 1] == terrain::Road) {
					spritesToDraw.push_back(roadSprites[4]);
				}
				if (y < mapData[x].size() - 1 && mapData[x][y + 1] == terrain::Road) {
					spritesToDraw.push_back(roadSprites[2]);
				}
				if (x > 0 && mapData[x - 1][y] == terrain::Road) {
					spritesToDraw.push_back(roadSprites[1]);
				}
				if (x < mapData.size() - 1 && mapData[x + 1][y] == terrain::Road) {
					spritesToDraw.push_back(roadSprites[3]);
				}

				// actually draws all the sprites onto the texture
				for (size_t i = 0; i < spritesToDraw.size(); i++) {

					spritesToDraw[i].setPosition(middle);
					window->draw(spritesToDraw[i]);
				}
			}
			else if (mapData[x][y] == terrain::House) {

				RectangleShape r = RectangleShape(Vector2f(5, 5));
				r.setFillColor(Color::Blue);
				r.setPosition(middle);
				window->draw(r);

			}

			// creates a new rectangle
			sf::RectangleShape middlePoint(sf::Vector2f(1, 1));
			middlePoint.setFillColor(sf::Color::Red);

			// sets the rect's position
			middlePoint.setPosition(middle);

			// draws the point
			window->draw(middlePoint);

		}
	}

	// draws a debug grid
	/*for (size_t x = 0; x < mapData.size(); x++) {

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

	}*/
}

void GameMap::renderBuildings(RenderWindow * window, FloatRect clipRect)
{

	for (Building * b : buildings) {

		if (clipRect.contains(App::getRenderCoords(b->getPosition()))) {
			b->render(window);
		}
	}

}