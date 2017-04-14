#include "PostOffice.h"
#include "App.h"

PostOffice::PostOffice(App * app, Vector2i pos, Direction d) : Building(app, pos, d, "assets/sprites/office/office.png") {

	NodeMap * nodeMap = app->getGameMap()->getRoadMap();
	Vector2i node = nodeMap->getNode(nodeMap->getConnections()[this->roadConnIndex].first);

	std::cout << "I am connected to " << node.x << ", " << node.y;
}

void PostOffice::update(Time dt) {

}