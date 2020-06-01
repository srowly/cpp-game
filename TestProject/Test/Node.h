#include <vector>
#include "Tile.h"
#include "Vector2.h"
#include "Grid.h"

#pragma once
class Node
{
public:
	Vector2<int> size;
	Grid grid;
	Grid* room;

	Node* leftChild;
	Node* rightChild;

	Node(Grid grid);
	~Node();
};

