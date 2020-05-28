#include "CorridorGenerator.h"

CorridorGenerator(Level level, CorridorType type)
{
    m_level = level;
    m_type = type;
}

void CorridorGenerator::PlaceCorridors(Node n)
{
    if (n.leftChild != NULL && n.rightChild != NULL)
    {
        GenNewCorridor(GetRoom(n.leftChild), GetRoom(n.rightChild));
        PlaceCorridors(n.leftChild);
        PlaceCorridors(n.rightChild);
    }
}

Tile[, ] CorridorGenerator::GetRoom(Node node)
{
    if (node.Room != null)
        return node.Room;
    else
    {
        Tile[, ] lRoom = null;
        Tile[, ] rRoom = null;

        if (node.LeftChild != null)
            lRoom = GetRoom(node.LeftChild);
        if (node.RightChild != null)
            rRoom = GetRoom(node.RightChild);

        if (lRoom == null && rRoom == null)
            return null;
        else if (lRoom == null)
            return rRoom;
        else if (rRoom == null)
            return lRoom;
        else if (Random.Range(0, 2) == 0)
            return lRoom;
        else
            return rRoom;
    }
}

void CorridorGenerator::GenNewCorridor(Tile[, ] roomOne, Tile[, ] roomTwo)
{
    if (roomOne == null || roomTwo == null)
        return;

    int[] lengths = GetRoomLengths(roomOne, roomTwo);

    switch (m_type)
    {
    case CorridorType.Straight:
        PlaceStraightCorridor(roomOne, roomTwo, lengths);
        break;
    case CorridorType.Bent:
        PlaceBentCorridor(roomOne, roomTwo, lengths);
        break;
    case CorridorType.ZigZag:
        PlaceZCorridor(roomOne, roomTwo, lengths);
        break;
    }
}

void CorridorGenerator::PlaceStraightCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, int[] lengths)
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

void CorridorGenerator::PlaceStraightXCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, int[] roomLengths)
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

void CorridorGenerator::PlaceStraightYCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, int[] roomLengths)
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

void CorridorGenerator::PlaceBentCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, int[] roomLengths)
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

void CorridorGenerator::PlaceZCorridor(Tile[, ] roomOne, Tile[, ] roomTwo, int[] roomLengths)
{
    Tile randTileOne = roomOne[Random.Range(0, roomLengths[0] - 1), Random.Range(0, roomLengths[1] - 1)];
    Tile randTileTwo = roomTwo[Random.Range(0, roomLengths[2] - 1), Random.Range(0, roomLengths[3] - 1)];

    int rOneX = randTileOne.GridPosition.x;
    int rOneY = randTileOne.GridPosition.y;
    int rTwoX = randTileTwo.GridPosition.x;
    int rTwoY = randTileTwo.GridPosition.y;

    if (rOneX < rTwoX)
    {
        int rNewX = GetHalfway(rTwoX, rOneX);
        PlaceCorridor(rOneX, rNewX + 1, rOneY, rOneY + 1);
        PlaceCorridor(rNewX, rTwoX, rTwoY, rTwoY + 1);

        if (rOneY < rTwoY)
            PlaceCorridor(rNewX, rNewX + 1, rOneY, rTwoY);
        else
            PlaceCorridor(rNewX, rNewX + 1, rTwoY, rOneY);
    }

    else
    {
        int rNewX = GetHalfway(rOneX, rTwoX);
        PlaceCorridor(rTwoX, rNewX + 1, rTwoY, rTwoY + 1);
        PlaceCorridor(rNewX, rOneX, rOneY, rOneY + 1);

        if (rOneY < rTwoY)
            PlaceCorridor(rNewX, rNewX + 1, rOneY, rTwoY);
        else
            PlaceCorridor(rNewX, rNewX + 1, rTwoY, rOneY);
    }
}

void CorridorGenerator::PlaceCorridor(int minX, int maxX, int minY, int maxY)
{
    var corridor = Grid.GetSection(m_level.Grid.Tiles, minX, maxX, minY, maxY);
    Grid.SetSection(corridor, Tile.Types.Floor, (obj) = > m_level.Floor.Add(obj));
    m_level.AddCorridor(new Corridor(corridor));
}

int CorridorGenerator::GetHalfway(int i, int j)
{
    float k = (float)i + (float)j;
    k = k / 2.0f;
    return (int)k;
}

int[] CorridorGenerator::GetRoomLengths(Tile[, ] roomOne, Tile[, ] roomTwo)
{
    int[] lengths = new int[4];
    lengths[0] = roomOne.GetLength(0);
    lengths[1] = roomOne.GetLength(1);
    lengths[2] = roomTwo.GetLength(0);
    lengths[3] = roomTwo.GetLength(1);

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