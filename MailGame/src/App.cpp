#include "App.h"
#include "windows.h"

App::App(const int W, const int H)
{
	m = GameMap();

	// both viewports show the whole map, but hudView scales
	// it down to 20% of the screen width
	gameView.reset(sf::FloatRect(0, 0, (float) W, (float) H));
	gameView.rotate(45);
	gameView.setSize((float) W, (float)(2 * H));

	hudView.reset(sf::FloatRect(0, 0, (float)W, (float)H));
	hudView.setViewport(sf::FloatRect(0, 0, 0.2f, 0.2f));
	
}

void App::init()
{
	m.init(200, 200, 0.2);
}

void App::update()
{

}

void App::render(sf::RenderWindow * window)
{

	int scale = 2;
	window->setView(gameView);
	m.renderRoads(window, scale);

	window->setView(hudView);
	m.debugRender(window, 0, 0, scale);
}

std::pair<int, int> App::getRenderCoords(std::pair<int, int> worldCoords)
{
	return wordCoords;
}

void App::destroy()
{

}