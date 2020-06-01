#include <vector>
#include <stdlib.h>

#include "BSPParameters.h"
#include "Node.h"
#include "Level.h"
#include "Grid.h"

#pragma once
class CorridorGenerator
{
private:
    Level level;
    CorridorType type;

    TileGrid GetRoom(Node* node);
    void GenNewCorridor(TileGrid roomOne, TileGrid roomTwo);
    void PlaceStraightCorridor(TileGrid roomOne, TileGrid roomTwo, std::vector<int> lengths);
    void PlaceStraightXCorridor(TileGrid roomOne, TileGrid roomTwo, std::vector<int>  roomLengths);
    void PlaceStraightYCorridor(TileGrid roomOne, TileGrid roomTwo, std::vector<int>  roomLengths);
    void PlaceBentCorridor(TileGrid roomOne, TileGrid roomTwo, std::vector<int> roomLengths);
    void PlaceCorridor(int minX, int maxX, int minY, int maxY);
    int GetHalfway(int i, int j);
    std::vector<int>  GetRoomLengths(TileGrid roomOne, TileGrid roomTwo);
    bool CheckFacing(float minDimOne, float maxDimOne, float minDimTwo, float maxDimTwo);
    bool CheckIfBetween(float check, float min, float max);

public:
    CorridorGenerator(Level level, CorridorType type);
    void PlaceCorridors(Node* node);
};