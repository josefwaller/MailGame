#include "App.h"
#include "windows.h"

App::App(const int screenW, const int screenH, RenderWindow * gameWindow, tgui::Gui * gui)
{

	// sets width and height
	W = screenW;
	H = screenH;

	// saves the window and gui
	window = gameWindow;
	this->gui = gui;

	// creates HUD
	hud = Hud(this);
	hud.init();


	// creates map
	m = GameMap();

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
	debugView.setViewport(FloatRect(0, 0.1f, 0.2f, 0.2f));

	// sets up HUD view
	hudView.reset(FloatRect(0, 0, (float)W, (float)H));

}

void App::init()
{

	// checks I don't mess the coordinates up
	if (App::getGameCoordsFromRenderCoords(App::getRenderCoords({ 20, 02 })) != Vector2f(20, 2)) {
		cout << "Somehow, the coordinate functions have gotten out of sync!" << endl;
	}

	// initializes the GameMap
	m.init(200, 200, App::mapS);
}

void App::update(sf::Time dt)
{

	// updates the hud
	hud.update();

	// updates the buildings
	m.updateBuildings(dt);

	// moves the view
	moveView(dt);
}

void App::moveView(Time dt) {


	// gets the mouse position to move the screen left or right
	sf::Vector2i mPos = sf::Mouse::getPosition(*window);

	// the distance the move the camera in the x or y coordinate
	float disMoved[2] = { 0.0, 0.0 };

	// moves the secreen left/right
	if (Keyboard::isKeyPressed(Keyboard::Left)) {

		// moves the screen left
		disMoved[0] = -1 * screenSpeed * dt.asSeconds();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right)) {

		// moves the screen right
		disMoved[0] = screenSpeed * dt.asSeconds();

	}

	// moves the screen up/down
	if (Keyboard::isKeyPressed(Keyboard::Up)) {

		// moves the screen up
		disMoved[1] = -1 * screenSpeed * dt.asSeconds();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down)) {

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

	// draws the debug map
	window->setView(debugView);
	m.debugRender(window, clipRect);

	// draws the HUD
	window->setView(gameView);
	hud.render(window);
	
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
		(float) (worldCoords.x  - worldCoords.y),
		(float) (0.5 * (worldCoords.y + worldCoords.x)));

	// moves the coordinates over to not have negative x values
	rotatedCoords.x += mapS * App::getScale();

	// returns the new values
	return rotatedCoords;
}

Vector2f App::getGameCoordsFromRenderCoords(Vector2f renderCoords) {

	renderCoords.x -= mapS * App::getScale();

	return Vector2f(
		(float) (renderCoords.y + 0.5 * renderCoords.x) / App::getScale(),
		(float) (renderCoords.y - 0.5 * renderCoords.x) / App::getScale()
	);
}

Vector2f App::getGameCoordsFromScreen(Vector2i windowCoords) {

	window->setView(gameView);
	return App::getGameCoordsFromRenderCoords(window->mapPixelToCoords(windowCoords));
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
RenderWindow * App::getWindow() {
	return this->window;
}
GameMap * App::getGameMap() {
	return &this->m;
}

tgui::Gui * App::getGui() {
	return this->gui;
}