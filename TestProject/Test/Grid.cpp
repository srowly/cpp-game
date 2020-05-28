#include "Grid.h"

Grid::Grid(std::vector<std::vector<Tile> > tiles)
{
	this->tiles = tiles;
	x = tiles.size();
	y = tiles[0].size();
}