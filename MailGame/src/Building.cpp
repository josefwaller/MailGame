#pragma once

#include "Building.h"
#include "ResourceManager.h"
#include "App.h"

Building::Building(App * app, Vector2i startingPos, Direction dir, string spritePath = "") : Entity(app, (Vector2f)startingPos, dir)
{
	// loads the sprite if it is known when the constructor is called
	if (spritePath != "") {

		s = ResourceManager::get()->loadSprite(spritePath);

	}

	roadConnIndex = app->getGameMap()->getNodeConnection(startingPos);

}
void Building::render(RenderWindow * window)
{
	// sets the origin to the bottom-middle
	FloatRect bounds = s->getGlobalBounds();
	s->setOrigin(bounds.width / 2, bounds.height);

	// gets the point to draw
	Vector2f point = App::getRenderCoords(position + Vector2f(1, 1));
	s->setPosition(point);


	// draws 
	window->draw(*s);
}