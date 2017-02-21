#include "NodeMap.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include "windows.h"
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
	vector<Vector2i>::iterator i = std::find(nodes.begin(), nodes.end(), node);
	if (i == nodes.end()) {
		nodes.push_back(node);
	}
	else {
		return (int) distance(nodes.begin(), i);
	}
	
	// adds the connections
	for (int n : startingConnections) {
		connections.push_back({ (int) nodes.size(), n });
	}

	return (int)(nodes.size() - 1);
}

/*
 Adds a new node inbetween two nodes, so that it is connected to both and 
 separates them
*/
void NodeMap::splitConnection(int middleNode, int nodeOne, int nodeTwo)
{
	// removes the old connection
	removeConnection(nodeOne, nodeTwo);

	// adds the new connections
	addConnection(middleNode, nodeOne);
	addConnection(middleNode, nodeTwo);

}

bool inRange(int i, int numOne, int numTwo) {
	
	if (numOne < numTwo) {
		return (i >= numOne && i <= numTwo);
	}
	else {
		return (i <= numOne && i >= numTwo);
	}
}

// adds nodes at all intersections between connections
void NodeMap::addNodesAtIntersections()
{
	vector<pair<int, int>> cachedConnections(connections);

	for (size_t i = 0; i < cachedConnections.size(); i++) {

		for (size_t j = i + 1; j < cachedConnections.size(); j++) {

			pair<int, int> conOne = cachedConnections[i];
			pair<Vector2i, Vector2i> nodesOne(getNode(conOne.first), getNode(conOne.second));

			pair<int, int> conTwo = cachedConnections[j];
			pair<Vector2i, Vector2i> nodesTwo(getNode(conTwo.first), getNode(conTwo.second));

			int x;
			int y;

			if (nodesOne.first.x == nodesOne.second.x) {
				if (nodesTwo.first.y != nodesTwo.second.y) {
					continue;
				}
				x = nodesOne.first.x;
				y = nodesTwo.first.y;
			}
			else {
				if (nodesTwo.first.x != nodesTwo.second.x) {
					continue;

				}
				x = nodesTwo.first.x;
				y = nodesOne.first.y;
			}

			bool hasX = false;
			bool hasY = false;

			if (inRange(x, nodesOne.first.x, nodesOne.second.x)) {
				if (inRange(x, nodesTwo.first.x, nodesTwo.second.x)) {
					hasX = true;
				}
			}

			if (inRange(y, nodesOne.first.y, nodesOne.second.y)) {
				if (inRange(y, nodesTwo.first.y, nodesTwo.second.y)) {
					hasY = true;
				}
			}

			if (hasX && hasY) {

				std::cout << x << ":" << y << std::endl;

				int newNode = addNode(Vector2i(x, y));
				splitConnection(newNode, conOne.first, conOne.second);
				splitConnection(newNode, conTwo.first, conTwo.second);
			}

		}
	}
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