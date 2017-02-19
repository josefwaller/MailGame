#include "NodeMap.h"

#include <vector>
#include "SFML\Graphics.hpp"

using std::vector;
using std::pair;
using sf::Vector2i;

NodeMap::NodeMap(vector<Vector2i> startingNodes = {}, vector<pair<int, int>> startingConnections = {})
{

}

void NodeMap::addNode(Vector2i node, vector<pair<int, int>> connections = {})
{

}

void NodeMap::addConnection(int nodeOne, int nodeTwo)
{

}

bool NodeMap::isConnected(int nodeOne, int nodeTwo)
{

}

Vector2i NodeMap::getNode(int node)
{

}

vector<Vector2i> NodeMap::getNodes()
{

}

vector<pair<int, int>> NodeMap::getConnections()
{

}

vector<int> NodeMap::getNodeConnections(int node)
{

}