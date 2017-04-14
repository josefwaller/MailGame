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
}

void GameMap::updateBuildings(Time dt) 
{

	for(Building * b : buildings) {

		b->update(dt);

	}

}

void GameMap::addBuilding(Building * b) 
{

	buildings.push_back(b);

}

bool GameMap::isValidBuildingLocation(Vector2i pos)
{
	// if the terrain is not empty, it is not valid
	if (mapData[pos.x][pos.y] != terrain::Empty) return false;

	cout << "ASaaaaaaaDF";

	// checks it is connected to a road
	for (int xOff = -1; xOff <= 1; xOff++) {
		for (int yOff = -1; yOff <= 1; yOff++) {

			// skips checking if values are zero or it is diagonal or both 
			if (xOff != 0 && yOff != 0) {
				continue;
			}
			cout << xOff << ", " << yOff << endl;
			if (mapData[pos.x + xOff][pos.y + yOff] == terrain::Road) {
				return true;
			}
		}
	}

	return false;
}

int GameMap::getNodeConnection(Vector2i pos) {

	vector<pair<int, int>> conns = roadMap.getConnections();

	for (size_t i = 0; i < conns.size(); i++) {

		Vector2i nOne = roadMap.getNode(conns[i].first);
		Vector2i nTwo = roadMap.getNode(conns[i].second);

		if (nOne.x == nTwo.x) {
			if (abs(pos.x - nOne.x)) {
				return (int)i;
			}
			else if (nOne.x == pos.x) {

				if (abs(pos.y - nOne.y) == 1 || abs(pos.y - nTwo.y) == 1) {
					return (int)i;
				}

			}
		} else if (nOne.y == nTwo.y) {
			if (abs(nOne.y - pos.y)) {
				return (int)i;
			}
			else if (nOne.y == pos.y) {
				if (abs(nOne.x - pos.x) == 1 || abs(nTwo.x - pos.x) == 1) {
					return (int)i;
				}
			}
		} else {
		
			cout << "Something went wrong with the nodemap" << endl;
		}
	}
	return -1;
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
							if (mapData.size() < (unsigned int) (x + xOff) || mapData[0].size() < (unsigned int) (y + yOff)) {
								continue;
							}

							// checks the terrain is empty
							if (mapData[x + xOff][y + yOff] == terrain::Empty) {

								// there is a 80% chance to just not add a house, to keep empty space
								if (rand() % 100 < 80) {
									continue;
								}

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
								buildings.push_back(new House(Vector2i((int)(x + xOff), (int)(y + yOff)), hDir));

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
	// destroys all the buildings
	for (auto b : buildings) {
		delete b;
	}
}

sf::Sprite GameMap::loadTileSprite(string fPath)
{
	sf::Sprite sprite = sf::Sprite(*ResourceManager::get()->loadSprite(fPath));

	// sets the origin to center so they can be easily drawn
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	sprite.setOrigin(
		(float) (0.5 * spriteBounds.width), 
		(float) (0.5 * spriteBounds.height));

	Vector2f origin = App::getRenderCoords(Vector2f(0, 0));
	Vector2f end = App::getRenderCoords(Vector2f(1, 1));

	float scale = (end.y - origin.y) / spriteBounds.height;
	sprite.setScale(scale, scale);

	return sprite;
}

void GameMap::debugRender(sf::RenderWindow * window, FloatRect clipRect)
{
	// draws a grid of the terrain behind the nodemap
	for (size_t x = 0; x < mapData.size(); x++) {
		for (size_t y = 0; y < mapData[x].size(); y++) {

			Vector2f renderCoords = App::getRenderCoords({ (float)x, (float)y });

			if (clipRect.contains(renderCoords)) {

				Color tileColor;

				// sets the color depending on the tile type
				switch (mapData[x][y]) {

				case terrain::Empty:
					tileColor = Color(0, 124, 6);
					break;

				case terrain::Road:
					tileColor = Color(79, 79, 79);
					break;

				case terrain::House:
					tileColor = Color(155, 0, 0);
					break;

				}

				// the 4 points around the tile
				Vertex points[] = {
					Vertex(renderCoords, tileColor),
					Vertex(App::getRenderCoords({ (float)x, (float)(y + 1) }), tileColor),
					Vertex(App::getRenderCoords({ (float)(x + 1), (float)(y + 1) }), tileColor),
					Vertex(App::getRenderCoords({ (float)(x + 1), (float)y }), tileColor)
				};

				window->draw(points, 4, Quads);
			}

		}
	}

	for (size_t i = 0; i < roadMap.getConnections().size(); i++) {
		
		// gets the 2 nodes to draw a line inbetween
		Vector2i nodeOne = roadMap.getNode(roadMap.getConnections()[i].first);
		Vector2i nodeTwo = roadMap.getNode(roadMap.getConnections()[i].second);

		// gets the render coordsinates for these nodes
		Vector2f renderNodeOne = App::getRenderCoords((Vector2f) nodeOne);
		Vector2f renderNodeTwo = App::getRenderCoords((Vector2f) nodeTwo);

		// creates a line inbetween the render coodinates
		Vertex line[] = {
			Vertex((Vector2f)renderNodeOne),
			Vertex((Vector2f)renderNodeTwo)
		};
		 // draws the line
		window->draw(line, 2, Lines);

	}

	for (size_t i = 0; i < roadMap.getNodes().size(); i++) {

		// gets the node
		Vector2i node = roadMap.getNode((int)i);

		// gets the render position for the node
		Vector2f renderNode = App::getRenderCoords((Vector2f)node);

		// creates a circle to draw at the node
		sf::CircleShape circ((float) (App::getScale() * 0.5));

		circ.setOrigin(circ.getRadius() / 2.0f, circ.getRadius() / 2.0f);

		// sets the position
		circ.setPosition(renderNode.x, renderNode.y);

		// sets color
		circ.setFillColor(sf::Color(255, 0, 0, 200));

		// draws the circle
		window->draw(circ);

	}

}

void GameMap::renderRoads(sf::RenderWindow * window, FloatRect clipRect)
{

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
				(float) (x + 0.5),
				(float) (y + 0.5)
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

			// creates a new rectangle
			RectangleShape middlePoint(Vector2f(1, 1));
			middlePoint.setFillColor(Color::Red);

			// sets the rect's position
			middlePoint.setPosition(middle);

			// draws the point
			window->draw(middlePoint);

		}
	}
}

void GameMap::renderBuildings(RenderWindow * window, FloatRect clipRect)
{

	for (Building * b : buildings) {

		if (clipRect.contains(App::getRenderCoords(b->getPosition()))) {
			b->render(window);
		}
	}

}