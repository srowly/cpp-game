#include "CorridorGenerator.h"

CorridorGenerator::CorridorGenerator(Level level, CorridorType type)
{
    this->level = level;
    this->type = type;
}

void CorridorGenerator::PlaceCorridors(Node* node)
{
    if (node->leftChild != NULL && node->rightChild != NULL)
    {
        GenNewCorridor(GetRoom(node->leftChild), GetRoom(node->rightChild));
        PlaceCorridors(node->leftChild);
        PlaceCorridors(node->rightChild);
    }
}

TileGrid CorridorGenerator::GetRoom(Node* node)
{
    if (node->room != NULL)
        return node->room->tiles;
    else
    {
        TileGrid lRoom;
        TileGrid rRoom;

        if (node->leftChild != NULL)
            lRoom = GetRoom(node->leftChild);
        if (node->rightChild != NULL)
            rRoom = GetRoom(node->rightChild);

        if (lRoom == NULL && rRoom == NULL)
            return null;
        else if (lRoom == NULL)
            return rRoom;
        else if (rRoom == NULL)
            return lRoom;
        else if rand() % nodeX / 2 + 1;
            return lRoom;
        else
            return rRoom;
    }
}

void CorridorGenerator::GenNewCorridor(TileGrid roomOne, TileGrid roomTwo)
{
    if (roomOne == NULL || roomTwo == NULL)
        return;

    auto lengths = GetRoomLengths(roomOne, roomTwo);

    switch (type)
    {
        case Straight:
            PlaceStraightCorridor(roomOne, roomTwo, lengths);
            break;
    }
}

void CorridorGenerator::PlaceStraightCorridor(TileGrid roomOne, TileGrid roomTwo, std::vector<int> lengths)
{
    Vector2 botLeftOne = roomOne[0, 0].GridPosition;
    Vector2 topRightOne = roomOne[roomOne.GetLength(0) - 1, roomOne.GetLength(1) - 1].GridPosition;
    Vector2 botLeftTwo = roomTwo[0, 0].GridPosition;
    Vector2 topRightTwo = roomTwo[roomTwo.GetLength(0) - 1, roomTwo.GetLength(1) - 1].GridPosition;

    bool xAligned = false;
    bool yAligned = false;

    if (CheckFacing(botLeftOne.x, topRightOne.x, botLeftTwo.x, topRightTwo.x))
        yAligned = true;
    else if (CheckFacing(botLeftOne.y, topRightOne.y, botLeftTwo.y, topRightTwo.y))
        xAligned = true;

    if (xAligned)
    {
        if (roomOne[0, 0].GridPosition.x > roomTwo[0, 0].GridPosition.x)
        {
            Tile[, ] temp = roomOne;
            roomOne = roomTwo;
            roomTwo = temp;
        }

        PlaceStraightXCorridor(roomOne, roomTwo, lengths);

    }

    else if (yAligned)
    {
        if (roomOne[0, 0].GridPosition.y > roomTwo[0, 0].GridPosition.y)
        {
            Tile[, ] temp = roomOne;
            roomOne = roomTwo;
            roomTwo = temp;
        }

        PlaceStraightYCorridor(roomOne, roomTwo, lengths);
    }
    else
    {
        PlaceBentCorridor(roomOne, roomTwo, lengths);
    }
}

void CorridorGenerator::PlaceStraightXCorridor(TileGrid roomOne, TileGrid roomTwo, std::vector<int> roomLengths)
{
    List<int> possiblePositions = new List<int>();

    for (int i = 0; i < roomLengths[1]; i++)
    {
        for (int j = 0; j < roomLengths[3]; j++)
        {
            int rOneY = roomOne[roomLengths[0] - 1, i].GridPosition.y;
            int rTwoY = roomTwo[roomLengths[2] - 1, j].GridPosition.y;

            if (rOneY == rTwoY)
                possiblePositions.Add(rOneY);
        }
    }

    int rOneX = roomOne[roomLengths[0] - 1, 0].GridPosition.x;
    int rTwoX = roomTwo[0, 0].GridPosition.x;
    int chosenY = possiblePositions[Random.Range(0, possiblePositions.Count)];
    PlaceCorridor(rOneX + 1, rTwoX, chosenY, chosenY + 1);
}

void CorridorGenerator::PlaceStraightYCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, std::vector<int> roomLengths)
{
    List<int> possiblePositions = new List<int>();

    for (int i = 0; i < roomLengths[0]; i++)
    {
        for (int j = 0; j < roomLengths[2]; j++)
        {
            int rOneX = roomOne[i, roomLengths[1] - 1].GridPosition.x;
            int rTwoX = roomTwo[j, roomLengths[3] - 1].GridPosition.x;

            if (rOneX == rTwoX)
                possiblePositions.Add(rOneX);
        }
    }

    int rOneY = roomOne[0, roomLengths[1] - 1].GridPosition.y;
    int rTwoY = roomTwo[0, 0].GridPosition.y;
    int chosenX = possiblePositions[Random.Range(0, possiblePositions.Count)];
    PlaceCorridor(chosenX, chosenX + 1, rOneY + 1, rTwoY);
}

void CorridorGenerator::PlaceBentCorridor(TileGrid roomOne, TileGrid roomTwo, std::vector<int> roomLengths)
{
    Tile randTileOne = roomOne[Random.Range(0, roomLengths[0] - 1), Random.Range(0, roomLengths[1] - 1)];
    Tile randTileTwo = roomTwo[Random.Range(0, roomLengths[2] - 1), Random.Range(0, roomLengths[3] - 1)];

    int rOneX = randTileOne.GridPosition.x;
    int rOneY = randTileOne.GridPosition.y;
    int rTwoX = randTileTwo.GridPosition.x;
    int rTwoY = randTileTwo.GridPosition.y;

    if (rOneX < rTwoX)
    {
        PlaceCorridor(rOneX, rTwoX + 1, rOneY, rOneY + 1);

        if (rOneY < rTwoY)
            PlaceCorridor(rTwoX, rTwoX + 1, rOneY, rTwoY);
        else
            PlaceCorridor(rTwoX, rTwoX + 1, rTwoY, rOneY);
    }

    else
    {
        PlaceCorridor(rTwoX, rOneX + 1, rOneY, rOneY + 1);

        if (rOneY < rTwoY)
            PlaceCorridor(rTwoX, rTwoX + 1, rOneY, rTwoY);
        else
            PlaceCorridor(rTwoX, rTwoX + 1, rTwoY, rOneY);
    }
}


void CorridorGenerator::PlaceCorridor(int minX, int maxX, int minY, int maxY)
{
    TileGrid corridor = Grid::GetSection(level.grid.tiles, minX, maxX, minY, maxY);
    std::function<void(Tile)> lambda = [&](Tile t) { level.floor.insert(t); };
    Grid::SetSection(corridor, Tile::Types::Floor, lambda);
    level.AddCorridor(corridor);
}

int CorridorGenerator::GetHalfway(int i, int j)
{
    float k = (float)i + (float)j;
    k = k / 2.0f;
    return (int)k;
}

std::vector<int> CorridorGenerator::GetRoomLengths(TileGrid roomOne, TileGrid roomTwo)
{
    std::vector<int> lengths;
    lengths[0] = roomOne.size();
    lengths[1] = roomOne[0].size();
    lengths[2] = roomTwo.size();
    lengths[3] = roomTwo[0].size();

    return lengths;
}

bool CorridorGenerator::CheckFacing(float minDimOne, float maxDimOne, float minDimTwo, float maxDimTwo)
{
    if (CheckIfBetween(minDimOne, minDimTwo, maxDimTwo) || CheckIfBetween(minDimTwo, minDimOne, maxDimOne))
        return true;
    else
        return false;
}

bool CorridorGenerator::CheckIfBetween(float check, float min, float max)
{
    if (check > min && check < max)
        return true;
    else
        return false;
}