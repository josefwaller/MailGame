#include "NodeMap.h"

#include <vector>
#include "SFML\Graphics.hpp"

using std::vector;
using std::pair;
using sf::Vector2i;

NodeMap::NodeMap(vector<Vector2i> startingNodes, vector<pair<int, int>> startingConnections)
{
	nodes = startingNodes;
	connections = startingConnections;
}

int NodeMap::addNode(Vector2i node, vector<int> startingConnections)
{
	// adds the node
	nodes.push_back(node);
	
	// adds the connections
	for (int n : startingConnections) {
		connections.push_back({ (int) nodes.size(), n });
	}

	return (int)(connections.size() - 1);
}

/*
 Adds a new node inbetween two nodes, so that it is connected to both and 
 separates them
*/
int NodeMap::splitConnection(Vector2i node, int nodeOne, int nodeTwo)
{

	// adds the new node
	int newNode = addNode(node);

	// removes the old connection
	removeConnection(nodeOne, nodeTwo);

	// adds the new connections
	addConnection(newNode, nodeOne);
	addConnection(newNode, nodeTwo);

	return newNode;

}

void NodeMap::removeConnection(int nodeOne, int nodeTwo)
{
	for (size_t i = 0; i < connections.size(); i++) {
		pair<int, int> c = connections[i];
		if (c.first == nodeOne || c.second == nodeOne) {
			if (c.first == nodeTwo || c.second == nodeTwo) {

				// removes the connection
				connections.erase(connections.begin() + i);
			}
		}
	}
}

void NodeMap::addConnection(int nodeOne, int nodeTwo)
{
	connections.push_back({ nodeOne, nodeTwo });
}

bool NodeMap::isConnected(int nodeOne, int nodeTwo)
{
	for (pair<int, int> c : connections) {

		if (c.first == nodeOne || c.second == nodeOne) {
			if (c.first == nodeTwo || c.second == nodeTwo) {
				return true;
			}
		}

	}

	return false;
}

bool NodeMap::hasNode(Vector2i position)
{
	for (Vector2i node : nodes) {
		if (node == position) {
			return true;
		}
	}
	return false;
}

Vector2i NodeMap::getNode(int node)
{
	return nodes[node];
}

vector<Vector2i> NodeMap::getNodes()
{
	return nodes;
}

vector<pair<int, int>> NodeMap::getConnections()
{
	return connections;
}

vector<int> NodeMap::getNodeConnections(int node)
{

	vector<int> nodeConnections = {};

	for (pair<int, int> c : connections) {

		if (c.first == node) {
			nodeConnections.push_back(c.second);
		}
		else if (c.second == node) {
			nodeConnections.push_back(c.first);
		}

	}

	return nodeConnections;
}