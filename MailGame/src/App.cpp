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
	gameView.reset(sf::FloatRect((mapS * App::getScale() - W) / 2, (mapS * App::getScale() - H) / 2, (float)W, (float)H));

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

	int scale = App::getScale();
	window->setView(gameView);
	m.renderRoads(window, scale);
	m.renderBuildings(window);

	window->setView(hudView);
	m.debugRender(window, 0, 0, scale);
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
		ceil(worldCoords.x  - worldCoords.y),
		ceil(0.5 * (worldCoords.y + worldCoords.x)));

	// moves the coordinates over to not have negative x values
	rotatedCoords.x += mapS * App::getScale();

	return rotatedCoords;
}

void App::destroy()
{
	m.destroy();
}