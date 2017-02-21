#include "App.h"
#include "windows.h"

App::App(const int W, const int H)
{
	m = GameMap();

	gameView.reset(sf::FloatRect(0, 0, W, H));

	gameView.setRotation(45);
	gameView.setSize(W, H * 2);

	hudView.reset(sf::FloatRect(0, 0, 200, 200));

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
	window->setView(gameView);
	m.renderRoads(window);

	window->setView(hudView);
	m.debugRender(window, 0, 0, 10);
}

void App::destroy()
{

}