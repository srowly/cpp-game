#include "Node.h"
#include "BSPAlgorithm.h"

#pragma once
class RoomGenerator
{
public:
	RoomGenerator(int minWidth, int minHeight, BSPAlgorithm& bspAlgo);
	void PlaceRooms(Node* n);
	int roomNumber;

private:
	int minWidth;
	int minHeight;
	BSPAlgorithm& bspAlgo;

	void GenNewRoom(Node* n);
};

