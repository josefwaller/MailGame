#include "House.h"
#include "ResourceManager.h"
#include <ctime>

House::House(Vector2f pos, Direction dir) : Building(pos, dir, "")
{

	// the different models of houses
	vector<string> models = { "house_1", "house_2" };

	// the different roof colors for each model
	map<string, vector<string>> roofColors = {
		{"house_1",  {"blue", "red", "grey"}},
		{"house_2", {"blue", "red", "black", "purple"}}
	};

	// the different body colors for each model
	map<string, vector<string>> bodyColors = {
		{"house_1", {"white", "grey"}},
		{"house_2", {"white", "grey", "cream"}}
	};

	// randomly determines the model
	string model = models[rand() % models.size()];

	// randomly determines the roof color
	string roofColor = roofColors[model][rand() % roofColors[model].size()];

	// randomly determines the body color
	string bodyColor = bodyColors[model][rand() % bodyColors[model].size()];

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

	string spritePath = "assets/sprites/houses/" + model + "/" + model + "_" + dirStr + "_" + bodyColor + "_" + roofColor + ".png";

	s = ResourceManager::get()->loadSprite(spritePath);

}
void House::update(Time dt)
{

}