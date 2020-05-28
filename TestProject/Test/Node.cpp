#include "Node.h"

Node::Node(Grid grid)
{
	this->grid = grid;
	size = { grid.size(), grid[0].size() };
	leftChild = NULL;
	rightChild = NULL;
};

Node::~Node()
{
	delete leftChild;
	delete rightChild;
};