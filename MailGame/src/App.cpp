#include "App.h"
#include "windows.h"

App::App(const int screenW, const int screenH, RenderWindow * gameWindow)
{

	// sets width and height
	W = screenW;
	H = screenH;

	// creates HUD
	hud = Hud(this);

	// creates map
	m = GameMap();

	// starts deltaTime
	deltaClock.restart();

	// saves the window
	window = gameWindow;

	// both viewports show the whole map, but dubView scales
	// it down to 20% of the screen width
	gameView.reset(sf::FloatRect(
		0, 
		0, 
		(float) W, 
		(float) H));

	// draws debug info
	// ex: nodemap
	debugView.reset(FloatRect(0, 0, (float) W, (float) H));
	debugView.setViewport(FloatRect(0, 0, 0.2f, 0.2f));

	// hudView has a width and height of 100
	// so positionin in the HUD is done in percentage
	hudView.reset(FloatRect(0, 0, 100.0f, 100.0f));
	hudView.setViewport(FloatRect(0, 0, 1.0f, 1.0f));

}

void App::init()
{

	// initializes the GameMap
	m.init(200, 200, App::mapS);
}

void App::update()
{

	// gets the delta time
	sf::Time dt = deltaClock.restart();

	// gets the mouse position to move the screen left or right
	sf::Vector2i mPos = sf::Mouse::getPosition(*window);

	// the distance the move the camera in the x or y coordinate
	double disMoved[2] = { 0.0, 0.0 };

	// moves the secreen left/right
	if (mPos.x < W * mouseThreshold) {

		// moves the screen left
		disMoved[0] = -1 * screenSpeed * dt.asSeconds();
	}
	else if (mPos.x > W - W * mouseThreshold) {
		
		// moves the screen right
		disMoved[0] = screenSpeed * dt.asSeconds();

	}

	// moves the screen up/down
	if (mPos.y < H * mouseThreshold) {
		
		// moves the screen up
		disMoved[1] = -1 * screenSpeed * dt.asSeconds();
	}
	else if (mPos.y > H - H * mouseThreshold) {
		
		// moves the screen down
		disMoved[1] = screenSpeed * dt.asSeconds();
	}

	// moves the gamemap
	gameView.move(disMoved[0], disMoved[1]);

	// moves the debug map
	debugView.move(disMoved[0], disMoved[1]);
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

	// gets a FloatRect which coverers the entire area which needs to be drawn
	// anything outside of clipRect will be clipped
	FloatRect clipRect(
		origin.x - tileW, 
		origin.y - tileH, 
		endPoint.x - origin.x + 2 * tileW, 
		endPoint.y - origin.y + 2 * tileH);

	// draws the roads
	m.renderRoads(window, clipRect);

	// draws the buildings
	m.renderBuildings(window, clipRect);

	// draws the HUD
	window->setView(hudView);
	hud.render(window);

	// draws the debug map
	window->setView(debugView);
	m.debugRender(window, clipRect);
	
}

int App::getScale()
{
	return 40;
}

// converts world coords to render coords
sf::Vector2f App::getRenderCoords(Vector2f worldCoords)
{

	// scales up by App::getScale()
	worldCoords.x *= App::getScale();
	worldCoords.y *= App::getScale();

	// creates a new pair of X, Y coordinates
	Vector2f rotatedCoords(
		(float) ceil(worldCoords.x  - worldCoords.y),
		(float) ceil(0.5 * (worldCoords.y + worldCoords.x)));

	// moves the coordinates over to not have negative x values
	rotatedCoords.x += mapS * App::getScale();

	// returns the new values
	return rotatedCoords;
}

// destroys everything on the heap
void App::destroy()
{
	// destroys the gamemap
	m.destroy();
}

// get/set methods
int App::getW() {
	return W;
}

int App::getH() {
	return H;
}