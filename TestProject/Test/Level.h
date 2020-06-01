#include <unordered_set>

#include "Grid.h"

#pragma once
class Level
{
public:
	Grid grid;
	std::unordered_set<Tile> floor;

    void AddRoom(TileGrid room);
    void AddCorridor(TileGrid corridor);
    void RemoveRoom(TileGrid room);
    void RemoveCorridor(TileGrid corridor);

private:
    std::unordered_set<TileGrid> roomsAndCorridors;
    std::unordered_set<TileGrid> rooms;
    std::unordered_set<TileGrid> corridors;
};

