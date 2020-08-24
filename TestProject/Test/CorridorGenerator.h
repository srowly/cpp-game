#include "Tile.h"
#include "BSPAlgorithm.h"

#pragma once
class CorridorGenerator 
{
public:
	std::vector<TileGrid> corridors;

	CorridorGenerator(BSPAlgorithm& bsp);
	void PlaceCorridors(Node* node);

private:
	BSPAlgorithm& bsp;

	TileGrid GetRoom(Node* n);

	void GenNewCorridor(TileGrid roomOne, TileGrid roomTwo);

	void PlaceStraightXCorridor(TileGrid roomOne, TileGrid roomTwo);

	//Places a straight corridor between two aligned tiles of the two rooms on the y axis.
	void PlaceStraightYCorridor(TileGrid roomOne, TileGrid roomTwo);

	void PlaceBentCorridor(TileGrid roomOne, TileGrid roomTwo);

	//Returns the half way point(average) between two integers.
	int GetHalfway(int i, int j);

	//Checks if two rooms are facing in the x or y axis.
	bool CheckFacing(float minDimOne, float maxDimOne, float minDimTwo, float maxDimTwo);

	//Checks if one position on the grid lies between two others.
	bool CheckIfBetween(float check, float min, float max);
};

