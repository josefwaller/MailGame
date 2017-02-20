#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using std::vector;
using std::pair;
using sf::Vector2i;

class NodeMap
{
private:
	// the nodes
	std::vector<Vector2i> nodes;

	// the connections between nodes
	// stores the connections as the two indexes 
	std::vector<pair<int, int>> connections;

public:
	NodeMap(vector<Vector2i> startingNodes = {}, vector<pair<int, int>> startingConnections = {});
	int addNode(Vector2i position, vector<int> startingConnections = {});

	void crossConnections();
	int splitConnection(Vector2i node, int nodeOne, int nodeTwo);

	void addConnection(int nodeOne, int nodeTwo);
	void removeConnection(int nodeOne, int nodeTwo);

	bool isConnected(int nodeOne, int nodeTwo);
	bool hasNode(Vector2i position);

	vector<Vector2i> getNodes();
	Vector2i getNode(int node);
	vector<pair<int, int>> getConnections();
	vector<int> getNodeConnections(int node);
};