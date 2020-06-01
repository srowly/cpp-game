
#include "Level.h"

void Level::AddRoom(TileGrid room)
{
    rooms.insert(room);
    roomsAndCorridors.insert(room);
}

void Level::RemoveRoom(TileGrid room)
{
    rooms.erase(room);
    roomsAndCorridors.erase(room);
}

void Level::AddCorridor(TileGrid corridor)
{
    corridors.insert(corridor);
    roomsAndCorridors.insert(corridor);
}

void Level::RemoveCorridor(TileGrid corridor)
{
    corridors.erase(corridor);
    roomsAndCorridors.erase(corridor);
}