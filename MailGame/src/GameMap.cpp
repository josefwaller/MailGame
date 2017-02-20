#include "GameMap.h"

#include "windows.h"

#include <vector>
#include <iostream>
#include <sstream>

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

	mapData.assign(30, std::vector<terrain>(30, terrain::Empty));

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

	// initializes the nodemap
	roadMap = NodeMap();

	// the list of accepted roads
	std::vector<road> roads = {};

	// the list of maybe acceptable roads
	std::vector<road> roadList = {};

	// the list of roads to check next time
	std::vector<road> tempRoads = {};

	// starts off with a road
	roadList.push_back({
		(int)(rand() % (mapData.size() - MAX_LENGTH)), 
		(int)(rand() % (mapData.size() - MAX_LENGTH)),
		(int)(rand() % (MAX_LENGTH / 2) + MAX_LENGTH / 2),
		true 
	});

	// does 15 degrees of roads
	for (int i = 0; i < FRACTAL_LIMIT; i++) {

		for (road r : roadList) {

			// checks if that road is acceptable
			bool valid = true;

			// checks if it is in bounds
			if (r.x < 0 || r.x + r.l > (int) mapData.size()) {
				valid = false;
			}
			if (r.y < 0 || r.y + r.l > (int) mapData[0].size()) {
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
				int nOne = roadMap.addNode(Vector2i(r.x, r.y));

				int nTwo;
				if (r.isH) {
					nTwo = roadMap.addNode(Vector2i(r.x + r.l, r.y));
				}
				else {
					nTwo = roadMap.addNode(Vector2i(r.x, r.y + r.l));
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

						tempRoads.push_back({ r.x - randOffset, r.y + rand() % r.l, newLength, true});

					}

				}

			} // if

		} // for

		roadList = tempRoads;

	}

	// adds them to the map
	for (size_t i = 0; i < roads.size(); i++) {

		road r = roads[i];

		for (int i = 0; i < r.l; i++) {
			if (r.isH) {
				mapData[r.x + i][r.y] = terrain::Road;
			}
			else {
				mapData[r.x][r.y + i] = terrain::Road;
			}
		}

	}

	// adds houses
	for (size_t x = 0; x < mapData.size(); x++) {
		for (size_t y = 0; y < mapData[x].size(); y++) {

			if (mapData[x][y] != terrain::Road) {

				// checks if the area has a road on some side
				int offsets[] = { -1, 0, 1 };

				for (int offX : offsets) {

					if ((int) mapData.size() <= x + offX || x + offX < 0) {
						continue;
					}

					for (int offY : offsets) {

						if ((int) mapData[x].size() <= y + offY || y + offY < 0) {
							continue;
						}

						if (mapData[x + offX][y + offY] == terrain::Road) {

							mapData[x][y] = terrain::House;

							// checks the next square
							goto outerLoops;
						}

					}
				}

			}

		outerLoops: ;
		}
	}

}

void GameMap::debugRender(sf::RenderWindow * window, int offX, int offY, int scale)
{
	/*
	for (size_t x = 0; x < mapData.size(); x++) {
		for (size_t y = 0; y < mapData[x].size(); y++) {

			sf::RectangleShape rect(sf::Vector2f((float)scale, (float)scale));
			rect.setPosition(sf::Vector2f((float)(offX + scale * x), (float)(offY + scale * y)));

			switch (mapData[x][y])
			{

				case terrain::Empty:
					rect.setFillColor(sf::Color::Green);
					break;

				case terrain::Road:
					rect.setFillColor(sf::Color(61, 61, 61));
					break;

				case terrain::House:
					rect.setFillColor(sf::Color::Red);
					break;
			}
			window->draw(rect);
		}
	}*/

	for (size_t i = 0; i < roadMap.getConnections().size(); i++) {

		OutputDebugString(L"Hello");
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

		Vector2i node = roadMap.getNode(i);

		sf::CircleShape circ((float)scale * 0.5);
		circ.setPosition((node.x - 0.5) * scale, (node.y - 0.5) * scale);
		circ.setFillColor(sf::Color::Red);

		window->draw(circ);

	}

}

void GameMap::renderRoads(sf::RenderWindow * window)
{

	sf::Texture roadTexture;

	std::string path = "assets/sprites/road.png";

	if (!roadTexture.loadFromFile(path)) {
		std::cout << "Failed to load texture at " << path << std::endl;
	}

	sf::Sprite roadSprite;
	roadSprite.setTexture(roadTexture);


}