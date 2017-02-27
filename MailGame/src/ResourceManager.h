#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

/*
Holds resources, most notably sprites and textures
*/
class ResourceManager
{
public:
	ResourceManager();
	static ResourceManager * get();
	Sprite * loadSprite(string url);

private:
	static ResourceManager r;
	map<string, pair<sf::Sprite, sf::Texture>> resources;
};