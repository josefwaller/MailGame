#include "House.h"
#include "ResourceManager.h"
#include <ctime>

House::House(Vector2f pos) : Building(pos, "")
{

	// randomly determines the roof color
	string roofColor = "";

	switch (rand() % 3) {
		case 0:
			roofColor = "grey";
			break;

		case 1:
			roofColor = "red";
			break;

		case 2:
			roofColor = "blue";
			break;
	}

	string bodyColor = "";
	
	switch (rand() % 2) {
	case 0:
		bodyColor = "grey";
		break;

	case 1:
		bodyColor = "white";
		break;
	}

	string spritePath = "assets/sprites/houses/house_1/house_1_right_" + bodyColor + "_" + roofColor + ".png";

	s = ResourceManager::get()->loadSprite(spritePath);

}
void House::update(Time dt)
{

}