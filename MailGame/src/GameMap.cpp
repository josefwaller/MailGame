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

	roadMap.addNodesAtIntersections();

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

		Vector2i node = roadMap.getNode(i);

		sf::CircleShape circ((float)scale * 0.5);
		circ.setPosition((node.x - 0.5) * scale, (node.y - 0.5) * scale);
		circ.setFillColor(sf::Color(255, 0, 0, 200));

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