#include "App.h"
#include "windows.h"

App::App(const int screenW, const int screenH, RenderWindow * gameWindow)
{
	m = GameMap();

	W = screenW;
	H = screenH;

	// starts deltaTime
	deltaClock.restart();

	// saves the window
	window = gameWindow;

	// both viewports show the whole map, but hudView scales
	// it down to 20% of the screen width
	gameView.reset(sf::FloatRect(
		(mapS * App::getScale() - W) / 2.0f, 
		(mapS * App::getScale() - H) / 2.0f, 
		(float) W, 
		(float) H));

	// draws debug info
	// ex: nodemap
	hudView.reset(sf::FloatRect(0, 0, (float)W, (float)H));
	hudView.setViewport(sf::FloatRect(0, 0, 0.2f, 0.2f));

}

void App::init()
{
	m.init(200, 200, App::mapS);
}

void App::update()
{

	sf::Time dt = deltaClock.restart();

	sf::Vector2i mPos = sf::Mouse::getPosition(*window);

	// moves the secreen left/right
	if (mPos.x < W * mouseThreshold) {
		gameView.move(-screenSpeed * dt.asSeconds(), 0);
	}
	else if (mPos.x > W - W * mouseThreshold) {
		
		gameView.move(screenSpeed * dt.asSeconds(), 0);

	}

	// moves the screen up/down
	if (mPos.y < H * mouseThreshold) {
		gameView.move(0, -screenSpeed * dt.asSeconds());
	}
	else if (mPos.y > H - H * mouseThreshold) {
		gameView.move(0, screenSpeed * dt.asSeconds());
	}
}

void App::render(sf::RenderWindow * window)
{
	// sets the view
	window->setView(gameView);

	// gets the bounding box of game elements to draw
	// to speed up processing power
	Vector2f origin = window->mapPixelToCoords({ 0, 0 });
	Vector2f endPoint = window->mapPixelToCoords({ W, H });

	// gets the width and height of a tile so as to not clip the tiles right at the edge
	float tileW = App::getRenderCoords({ 1, 0 }).x - App::getRenderCoords({ 0, 1 }).x;
	float tileH = App::getRenderCoords({ 1, 1 }).y - App::getRenderCoords({ 0, 0 }).y;

	FloatRect clipRect(origin.x - tileW, origin.y - tileH, endPoint.x - origin.x + 2 * tileW, endPoint.y - origin.y + 2 * tileH);

	m.renderRoads(window, clipRect);
	m.renderBuildings(window, clipRect);

	window->setView(hudView);
	m.debugRender(window, 0, 0);
}

int App::getScale()
{
	return 40;
}

sf::Vector2f App::getRenderCoords(sf::Vector2f worldCoords)
{

	worldCoords.x *= App::getScale();
	worldCoords.y *= App::getScale();

	// returns a new pair of X,Y coordinates
	sf::Vector2f rotatedCoords(
		(float) ceil(worldCoords.x  - worldCoords.y),
		(float) ceil(0.5 * (worldCoords.y + worldCoords.x)));

	// moves the coordinates over to not have negative x values
	rotatedCoords.x += mapS * App::getScale();

	return rotatedCoords;
}

void App::destroy()
{
	m.destroy();
}