#include "Grid.h"

Grid::Grid(TileGrid tiles)
{
	this->tiles = tiles;
	x = tiles.size();
	y = tiles[0].size();
}

TileGrid Grid::GetSection(TileGrid parentGrid, int minX, int maxX, int minY, int maxY)
{
    TileGrid newGrid;

    for (int i = minX; i < maxX; i++)
        for (int j = minY; j < maxY; j++)
            newGrid[i - minX, j - minY] = parentGrid[i, j];
    return newGrid;
}

void Grid::SetSection(TileGrid partition, Tile::Types type, std::function<void(Tile)> optionalOnSet)
{
    std::vector< std::vector<Tile> >::iterator row;
    std::vector<Tile>::iterator col;

    for (row = partition.begin(); row != partition.end(); ++row)
    {
        for (col = row->begin(); col != row->end(); ++col)
        {
            col->type = type;

            if (optionalOnSet)
            {
                optionalOnSet(*col);
            }
        }
    }
}
