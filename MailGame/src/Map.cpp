#include "Map.h"

#include "windows.h"

#include <vector>
#include <iostream>

enum class Map::terrain 
{
	Empty,
	Road
};

Map::Map()
{
}

void Map::init(const int W, const int H, double density)
{
	srand(time(0));

	mapData.assign(30, std::vector<terrain>(30, terrain::Empty));

	// NOTE TO SELF: These control what the map looks like
	const int MIN_LENGTH = 5;
	const int MAX_LENGTH = 20;
	const int NUM_OF_BRANCHES = 6;
	const int FRACTAL_LIMIT = 15;
	const int MAX_OFFSET = 8;
	const int MIN_OFFSET = 0;

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

	roadList.push_back({ 1, 1, 10, true });

	// does 5 degrees of roads
	for (int i = 0; i < FRACTAL_LIMIT; i++) {

		for (road r : roadList) {

			// checks if that road is acceptable
			bool valid = true;

			// checks if it is in bounds
			if (r.x < 0 || r.x + r.l > mapData.size()) {
				valid = false;
			}
			if (r.y < 0 || r.y + r.l > mapData[0].size()) {
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
	for (road r : roads) {

		for (int i = 0; i < r.l; i++) {
			if (r.isH) {
				mapData[r.x + i][r.y] = terrain::Road;
			}
			else {
				mapData[r.x][r.y + i] = terrain::Road;
			}
		}

	}

}

void Map::debugRender(sf::RenderWindow * window, int offX, int offY, int scale)
{

	for (int x = 0; x < mapData.size(); x++) {
		for (int y = 0; y < mapData[x].size(); y++) {

			sf::RectangleShape rect(sf::Vector2f(scale, scale));
			rect.setPosition(sf::Vector2f(offX + scale * x, offY + scale * y));

			switch (mapData[x][y])
			{

				case terrain::Empty:
					rect.setFillColor(sf::Color::Green);
					break;

				case terrain::Road:
					rect.setFillColor(sf::Color(61, 61, 61));
					break;
			}
			window->draw(rect);
		}
	}

}