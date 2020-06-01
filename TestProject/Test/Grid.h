#include <vector>
#include "Tile.h"
#include <functional>

using TileGrid = std::vector<std::vector<Tile> >;

#pragma once
class Grid
{
public:
	TileGrid tiles;
	int x;
	int y;

	Grid(TileGrid tiles);

	static TileGrid GetSection(TileGrid parentGrid, int minX, int maxX, int minY, int maxY);
	static void SetSection(TileGrid partition, Tile::Types type, std::function<void(Tile)> optionalOnSet);
};

