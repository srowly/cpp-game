#include "Node.h"

Node::Node() : identifier(0), size(0, 0)
{
	leftChild = NULL;
	rightChild = NULL;
};

Node::Node(TileGrid grid, int identifier) : grid(grid), size(grid.size(), grid[0].size()), identifier(identifier)
{
	leftChild = NULL;
	rightChild = NULL;
};

Node::~Node()
{
	if(leftChild != NULL)
		delete leftChild;

	if(rightChild != NULL)
		delete rightChild;
};