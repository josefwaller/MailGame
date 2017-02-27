#include "ResourceManager.h"
#include "SFML\Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;

ResourceManager::ResourceManager()
{
	resources = {};
}
ResourceManager ResourceManager::r = ResourceManager();

Sprite * ResourceManager::loadSprite(string fPath)
{
	map<string, pair<Sprite, Texture>>::iterator it = resources.find(fPath);
	if (it != resources.end())
	{
		return &resources[fPath].first;
	}

	// loads the texture
	Texture text;
	if (!text.loadFromFile(fPath))
	{
		cout << "File not found at " << fPath << endl;
	}

	// creates a new sprite
	Sprite s;

	// adds them to the map
	resources.insert(pair<string, pair<Sprite, Texture>>(fPath, pair<Sprite, Texture>(s, text)));

	// references the texture after it has been inserted into the map
	// so that the reference is to the map value
	resources[fPath].first.setTexture(resources[fPath].second);

	return &resources[fPath].first;
}

ResourceManager * ResourceManager::get()
{
	return &r;
}