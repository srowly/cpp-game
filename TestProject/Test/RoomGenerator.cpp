#include "RoomGenerator.h"

RoomGenerator::RoomGenerator(int minWidth, int minHeight, BSPAlgorithm& bspAlgo) : bspAlgo(bspAlgo)
{
	this->minWidth = minWidth;
	this->minHeight = minHeight;
	this->roomNumber = 0;
}


//Called by the BSPAlgo with the root node, moves through until leaf nodes found
//Attempts to add room to the subsection of the base grid referenced by these nodes.
void RoomGenerator::PlaceRooms(Node* n)
{
	if(n->leftChild == NULL && n->rightChild == NULL)
		GenNewRoom(n);
	
	if(n->leftChild != NULL)
		PlaceRooms(n->leftChild);
	if(n->rightChild != NULL)
		PlaceRooms(n->rightChild);
}

//
void RoomGenerator::GenNewRoom(Node* n)
{
	int maxWidth = n->size.x-1;
	int minWidth = 1;
	int maxHeight = n->size.y-1;
	int minHeight = 1;

	if (maxWidth-minWidth < this->minWidth || maxHeight-minHeight < this->minHeight)
		return;

	n->room = bspAlgo.getSection(n->grid, minWidth, maxWidth, minHeight, maxHeight);
	roomNumber++;
	printf("\nroomNumber:%d\n", roomNumber);
	printf("\n node: %d %d %d", n->identifier, n->size.x, n->size.y);
}