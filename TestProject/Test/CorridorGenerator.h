#include "BSPParameters.h"
#include "Node.h"

#pragma once
class CorridorGenerator
{
private:
    Level m_level;
    CorridorType m_type;

    Tile[, ] GetRoom(Node node);
    void GenNewCorridor(Tile[, ] roomOne, Tile[, ] roomTwo);
    void PlaceStraightCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, int[] lengths)
    void PlaceStraightXCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, int[] roomLengths);
    void PlaceStraightYCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, int[] roomLengths);
    void PlaceBentCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, int[] roomLengths);
    void PlaceZCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, int[] roomLengths);
    void PlaceCorridor(int minX, int maxX, int minY, int maxY);
    int GetHalfway(int i, int j);
    int[] GetRoomLengths(Tile[, ] roomOne, Tile[, ] roomTwo);
    bool CheckFacing(float minDimOne, float maxDimOne, float minDimTwo, float maxDimTwo);
    bool CheckIfBetween(float check, float min, float max);

public:
    CorridorGenerator(Level level, CorridorType type);
    void PlaceCorridors(Node n);
}