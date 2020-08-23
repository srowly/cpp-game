#include <vector>
#include <stdlib.h>  

#include "BSPParameters.h"
#include "Node.h"
#include "Vector2.h"

#pragma once
class BSPAlgorithm
{
private:
	Vector2<int> minNodeSize;
	int numNodes = 1;
public:
	Node* root;

	void Run(TileGrid& grid, BSPParameters parameters, int seed);
	void DivideGrid(TileGrid& parent, Node& node);

	TileGrid getSection(TileGrid parentGrid, int minX, int maxX, int minY, int maxY);
	void setSection(TileGrid partition, Tile::Types type, std::function<void(Tile*)> optionalOnSet);

	BSPAlgorithm();
	~BSPAlgorithm();
};