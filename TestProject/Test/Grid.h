#include <vector>
#include "Tile.h"

#pragma once
class Grid
{
public:
	std::vector<std::vector<Tile> > tiles;
	int x;
	int y;

	Grid(std::vector<std::vector<Tile> > tiles);
};

