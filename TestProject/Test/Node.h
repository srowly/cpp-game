#include <vector>
#include "Tile.h"
#include "Vector2.h"

#pragma once
class Node
{
public:
	int identifier;

	Vector2<int> size;
	TileGrid grid;

	Node* leftChild;
	Node* rightChild;

	TileGrid room;

	Node();
	Node(TileGrid grid, int indentifier);
	~Node();
};

