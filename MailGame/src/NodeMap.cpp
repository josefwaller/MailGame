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

// adds a node
int NodeMap::addNode(Vector2i node, vector<int> startingConnections)
{
	// checks if the node already exists
	vector<Vector2i>::iterator i = std::find(nodes.begin(), nodes.end(), node);

	if (i == nodes.end()) {

		// adds the node
		nodes.push_back(node);
	}
	else {

		// returns the existing node
		return (int) distance(nodes.begin(), i);
	}
	
	// adds the connections
	for (int n : startingConnections) {
		connections.push_back({ (int) nodes.size(), n });
	}

	// returns the new node
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

// checks if a number is inbetween two other numbers
// used for adding nodes at intersections
bool NodeMap::inRange(int i, int numOne, int numTwo) {
	
	if (numOne < numTwo) {
		return (i >= numOne && i <= numTwo);
	}
	else {
		return (i <= numOne && i >= numTwo);
	}
}

pair<Vector2i, Vector2i> NodeMap::getNodesFromConnection(int index)
{
	return pair<Vector2i, Vector2i>(
		getNode(connections[index].first),
		getNode(connections[index].second));
}

// adds nodes at all intersections between connections
void NodeMap::addNodesAtIntersections()
{

	// copies connections to avoid changing the index
	vector<pair<int, int>> cachedConnections(connections);

	for (size_t i = 0; i < cachedConnections.size(); i++) {

		// gets the first connection
		pair<int, int> conOne = cachedConnections[i];
		pair<Vector2i, Vector2i> nodesOne(getNode(conOne.first), getNode(conOne.second));

		for (size_t j = i + 1; j < cachedConnections.size(); j++) {

			// gets the second connection
			pair<int, int> conTwo = cachedConnections[j];
			pair<Vector2i, Vector2i> nodesTwo(getNode(conTwo.first), getNode(conTwo.second));

			/*
				Since there are only vertical and horizontal roads, we just need to check if
				one connection is vertical, one is horizontal and they both cross
			*/
			
			// these are the x and y coordinates of where the lines will cross
			int x;
			int y;

			if (nodesOne.first.x == nodesOne.second.x) {

				// if both nodes are vertical, they cannot cross
				if (nodesTwo.first.y != nodesTwo.second.y) {
					continue;
				}

				// copies x and y
				x = nodesOne.first.x;
				y = nodesTwo.first.y;
			}
			else {

				// if both nodes are horizontal, they cannot cross
				if (nodesTwo.first.x != nodesTwo.second.x) {
					continue;

				}
				
				// copies x and y
				x = nodesTwo.first.x;
				y = nodesOne.first.y;
			}

			// checks if the lines actually reach the x and y coordinates
			bool hasX = false;
			bool hasY = false;

			// checks if both lines reach the x coord
			if (inRange(x, nodesOne.first.x, nodesOne.second.x)) {
				if (inRange(x, nodesTwo.first.x, nodesTwo.second.x)) {
					hasX = true;
				}
			}

			// checks if both lines reach the y coord
			if (inRange(y, nodesOne.first.y, nodesOne.second.y)) {
				if (inRange(y, nodesTwo.first.y, nodesTwo.second.y)) {
					hasY = true;
				}
			}

			// checks if the lines intersect
			if (hasX && hasY) {

				// adds a new node
				int newNode = addNode(Vector2i(x, y));

				// removes the connections and adds new ones connection to the new node
				// Note: this will not affect cachedConnections
				splitConnection(newNode, conOne.first, conOne.second);
				splitConnection(newNode, conTwo.first, conTwo.second);
			}

		}
	}
}

// removes a connection between two nodes
void NodeMap::removeConnection(int nodeOne, int nodeTwo)
{
	// finds the connection
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

// adds a conection
void NodeMap::addConnection(int nodeOne, int nodeTwo)
{
	connections.push_back({ nodeOne, nodeTwo });
}

// checks if two nodes are connected directly
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

// checks if a node exists at a point
bool NodeMap::hasNode(Vector2i position)
{
	for (Vector2i node : nodes) {
		if (node == position) {
			return true;
		}
	}
	return false;
}

// gest a node at an index
Vector2i NodeMap::getNode(int node)
{
	return nodes[node];
}

// gets all nodes
vector<Vector2i> NodeMap::getNodes()
{
	return nodes;
}

// gets all connections
vector<pair<int, int>> NodeMap::getConnections()
{
	return connections;
}

// gets all connections attached to a node
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