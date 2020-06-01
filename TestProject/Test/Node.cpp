#include "Node.h"

Node::Node(Grid grid)
{
	this->grid = grid;
	size = { grid.tiles.size(), grid.tiles[0].size() };
	leftChild = NULL;
	rightChild = NULL;
	room = NULL;
};

Node::~Node()
{
	if(leftChild != NULL)
		delete leftChild;

	if(rightChild != NULL)
		delete rightChild;

	if(room != NULL)
		delete room;
};