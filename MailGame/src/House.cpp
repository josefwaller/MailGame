#include "House.h"
#include "ResourceManager.h"
#include <ctime>

House::House(Vector2f pos, Direction dir) : Building(pos, dir, "")
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

	// randomly determines the body color
	string bodyColor = "";
	
	switch (rand() % 2) {
	case 0:
		bodyColor = "grey";
		break;

	case 1:
		bodyColor = "white";
		break;
	}

	// sets direction
	string dirStr = "";

	switch (dir) {
	case Direction::Down:
		dirStr = "down";
		break;

	case Direction::Up:
		dirStr = "up";
		break;

	case Direction::Left:
		dirStr = "left";
		break;

	case Direction::Right:
		dirStr = "right";
		break;
	}

	string spritePath = "assets/sprites/houses/house_1/house_1_" + dirStr + "_" + bodyColor + "_" + roofColor + ".png";

	s = ResourceManager::get()->loadSprite(spritePath);

}
void House::update(Time dt)
{

}