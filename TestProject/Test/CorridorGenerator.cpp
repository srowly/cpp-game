#include "CorridorGenerator.h"

CorridorGenerator::CorridorGenerator(BSPAlgorithm& bsp) : bsp(bsp)
{

}

	//Loops through each node in the binary tree and places a corridor between its children.
void CorridorGenerator::PlaceCorridors(Node* n)
{
	if (n->leftChild != NULL && n->rightChild != NULL)
	{
		GenNewCorridor(GetRoom(n->leftChild), GetRoom(n->rightChild));
		PlaceCorridors(n->leftChild);
		PlaceCorridors(n->rightChild);
	}
}

TileGrid CorridorGenerator::GetRoom(Node* n)
{
	if (!n->room.empty())
		return n->room;
	else
	{
		TileGrid lRoom = {};
		TileGrid rRoom = {};

		if (n->leftChild != NULL)
			lRoom = GetRoom(n->leftChild);
		if (n->rightChild != NULL)
			rRoom = GetRoom(n->rightChild);

		if (lRoom.empty() && rRoom.empty())
			return {};
		else if (lRoom.empty())
			return rRoom;
		else if (rRoom.empty())
			return lRoom;
		else if (rand() % (2) == 0)
			return lRoom;
		else
			return rRoom;
	}
}

void CorridorGenerator::GenNewCorridor(TileGrid roomOne, TileGrid roomTwo)
{
	if (roomOne.empty() || roomTwo.empty())
		return;

	Vector2<int> botLeftOne = roomOne[0][0]->gridPosition;
	Vector2<int> topRightOne = roomOne[roomOne.size() - 1][roomOne[0].size() - 1]->gridPosition;
	Vector2<int> botLeftTwo = roomTwo[0][0]->gridPosition;
	Vector2<int> topRightTwo = roomTwo[roomTwo.size() - 1][roomTwo[0].size() - 1]->gridPosition;

	bool xAligned = CheckFacing(botLeftOne.y, topRightOne.y, botLeftTwo.y, topRightTwo.y);
	bool yAligned = CheckFacing(botLeftOne.x, topRightOne.x, botLeftTwo.x, topRightTwo.x);

	if (xAligned)
	{
		if (botLeftOne.x > botLeftTwo.x)
		{
			TileGrid temp = roomOne;
			roomOne = roomTwo;
			roomTwo = temp;
		}

		PlaceStraightXCorridor(roomOne, roomTwo);

	}
	else if (yAligned)
	{
		if (botLeftOne.y > botLeftTwo.y)
		{
			TileGrid temp = roomOne;
			roomOne = roomTwo;
			roomTwo = temp;
		}

		PlaceStraightYCorridor(roomOne, roomTwo);
	}
	else
	{
		PlaceBentCorridor(roomOne, roomTwo);
	}
}

//Places a straight corridor between two aligned tiles of the two rooms on the x axis.
void CorridorGenerator::PlaceStraightXCorridor(TileGrid roomOne, TileGrid roomTwo)
{
	std::vector<int> possiblePositions;
	TileGrid::iterator row;
	std::vector<Tile*>::iterator col;
	TileGrid::iterator row2;
	std::vector<Tile*>::iterator col2;

	for (row = roomOne.begin(); row != roomOne.end(); ++row)
	{
		for (col = row->begin(); col != row->end(); ++col)
		{
			for (row2 = roomTwo.begin(); row2 != roomTwo.end(); ++row2)
			{
				for (col2 = row2->begin(); col2 != row2->end(); ++col2)
				{
					if ((*col)->gridPosition.y == (*col2)->gridPosition.y)
						possiblePositions.push_back((*col)->gridPosition.y);
				}
			}
		}
	}

	int rOneX = roomOne[roomOne.size() - 1][0]->gridPosition.x;
	int rTwoX = roomTwo[0][0]->gridPosition.x;
	int chosenY = possiblePositions[rand() % possiblePositions.size()];
	corridors.push_back(bsp.getSection(bsp.grid, rOneX+1, rTwoX, chosenY, chosenY+1));
}

//Places a straight corridor between two aligned tiles of the two rooms on the y axis.
void CorridorGenerator::PlaceStraightYCorridor(TileGrid roomOne, TileGrid roomTwo)
{
	std::vector<int> possiblePositions;
	TileGrid::iterator row;
	TileGrid::iterator row2;

	for (row = roomOne.begin(); row != roomOne.end(); ++row)
	{
		for (row2 = roomTwo.begin(); row2 != roomTwo.end(); ++row2)
		{
			if ((*row)[0]->gridPosition.x == (*row2)[0]->gridPosition.x)
				possiblePositions.push_back((*row)[0]->gridPosition.x);
		}
	}


	int rOneY = roomOne[0][roomOne[0].size() - 1]->gridPosition.y;
	int rTwoY = roomTwo[0][0]->gridPosition.y;
	int chosenX = possiblePositions[rand() % possiblePositions.size()];
	corridors.push_back(bsp.getSection(bsp.grid, chosenX, chosenX+1, rOneY+1, rTwoY));
}

void CorridorGenerator::PlaceBentCorridor(TileGrid roomOne, TileGrid roomTwo)
{
	auto randTileOne = roomOne[rand() % roomOne.size()][rand() % roomOne[0].size()];
	auto randTileTwo = roomTwo[rand() % roomTwo.size()][rand() % roomTwo[0].size()];

	int rOneX = randTileOne->gridPosition.x;
	int rOneY = randTileOne->gridPosition.y;
	int rTwoX = randTileTwo->gridPosition.x;
	int rTwoY = randTileTwo->gridPosition.y;

	if (rOneX < rTwoX)
	{
		corridors.push_back(bsp.getSection(bsp.grid, rOneX, rTwoX + 1, rOneY, rOneY + 1));

		if (rOneY < rTwoY)
			corridors.push_back(bsp.getSection(bsp.grid, rTwoX, rTwoX + 1, rOneY, rTwoY));
		else
			corridors.push_back(bsp.getSection(bsp.grid, rTwoX, rTwoX + 1, rTwoY, rOneY));
	}
	else
	{
		corridors.push_back(bsp.getSection(bsp.grid, rTwoX, rOneX + 1, rOneY, rOneY + 1));

		if (rOneY < rTwoY)
			corridors.push_back(bsp.getSection(bsp.grid, rTwoX, rTwoX + 1, rOneY, rTwoY));
		else
			corridors.push_back(bsp.getSection(bsp.grid, rTwoX, rTwoX + 1, rTwoY, rOneY));
	}
}

//Returns the half way point(average) between two integers.
int CorridorGenerator::GetHalfway(int i, int j)
{
	float k = (float)i + (float)j;
	k = k / 2.0f;
	return (int)k;
}

//Checks if two rooms are facing in the x or y axis.
bool CorridorGenerator::CheckFacing(float minDimOne, float maxDimOne, float minDimTwo, float maxDimTwo)
{
	return CheckIfBetween(minDimOne, minDimTwo, maxDimTwo) || CheckIfBetween(minDimTwo, minDimOne, maxDimOne);
}

//Checks if one position on the grid lies between two others.
bool CorridorGenerator::CheckIfBetween(float check, float min, float max)
{
	return check > min && check < max;
}