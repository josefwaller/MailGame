#include "App.h"
#include "windows.h"

App::App()
{
	m = Map();
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
	m.debugRender(window, 0, 0, 10);
}

void App::destroy()
{

}