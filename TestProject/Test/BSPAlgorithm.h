#include <vector>
#include <stdlib.h>  

#include "Node.h"
#include "Vector2.h"

#include <list> 

#pragma once
class BSPAlgorithm
{
private:
	Vector2<int> minNodeSize;
	int numNodes = 0;
public:
	Node* root;
	std::list<Node*> nodes;

	void Run(TileGrid& grid, int seed);
	void DivideGrid(Node& node);

	TileGrid getSection(TileGrid parentGrid, int minX, int maxX, int minY, int maxY);
	void setSection(TileGrid partition, Tile::Types type, std::function<void(Tile*)> optionalOnSet);
	void forAllNodes(std::function<void(Node*)> onNode);
	BSPAlgorithm();
	~BSPAlgorithm();
};