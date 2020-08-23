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
	if (n->leftChild == NULL && n->rightChild == NULL)
		GenNewRoom(n);
	else
	{
		PlaceRooms(n->leftChild);
		PlaceRooms(n->rightChild);
	}
}

//
void RoomGenerator::GenNewRoom(Node* n)
{
	int maxWidth = n->size.x;
	int maxHeight = n->size.y;
	int midWidth = maxWidth / 2;
	int midHeight = maxHeight / 2;

	if (maxWidth < minWidth || maxHeight < minHeight)
		return;

	for (int i = 0; i < 100; i++)
	{
		//rand() % ((highestNumber - lowestNumber) + 1) + lowestNumber
		//Chooses 4 points in the node to act as the room corners.
		int botLeftX = rand() % (midWidth);
		int botLeftY = rand() % (midHeight);
		int topRightX = rand() % (maxWidth - midWidth) + midWidth;
		int topRightY = rand() % (maxHeight - midHeight) + midHeight;

		int width = topRightX - botLeftX;
		int height = topRightY - botLeftY;

		//If the room falls within the width and height limits its generated .
		if ((width > minWidth) && (height > minHeight))
		{
			if ((width < maxWidth) && (height < maxHeight))
			{
				n->room = bspAlgo.getSection(n->grid, botLeftX, topRightX, botLeftY, topRightY);
				roomNumber++;
				printf("\nroomNumber: %d width:%d height:%d\n", roomNumber, width, height);
				break;
			}
		}
	}
}