#include "RoomGenerator.h"


RoomGenerator::RoomGenerator(Level level, Vector2<int> minSize)
{
    this->minSize = minSize;
    this->level = level;
}

void RoomGenerator::PlaceRooms(Node node)
{
    if (node.leftChild == NULL && node.rightChild == NULL)
        GenNewRoom(node);
    else
    {
        PlaceRooms(node.leftChild);
        PlaceRooms(node.rightChild);
    }
}

void RoomGenerator::GenNewRoom(Node node)
{
    int nodeX = node.size.x;
    int nodeY = node.size.y;

    for (int i = 0; i < 50; i++)
    {
        int botLeftX = Random.Range(0, nodeX / 2);
        int botLeftY = Random.Range(0, nodeY / 2);
        int topRightX = Random.Range(nodeX / 2, nodeX);
        int topRightY = Random.Range(nodeY / 2, nodeY);

        int width = topRightX - botLeftX;
        int height = topRightY - botLeftY;

        float maxWidth = nodeX;
        float maxHeight = nodeY;

        int varyRoom = Random.Range(0, 3);
        if (varyRoom == 1)
        {
            maxWidth = Mathf.RoundToInt(maxWidth / 2f);
            maxHeight = Mathf.RoundToInt(maxHeight / 2f);
        }

        if (varyRoom == 2)
        {
            maxWidth = Mathf.RoundToInt(maxWidth / 1.5f);
            maxHeight = Mathf.RoundToInt(maxHeight / 1.5f);
        }

        if ((width > minSize.x) && (height > minSize.y))
        {
            if ((width < maxWidth) && (height < maxHeight))
            {
                node.Room = Grid.GetSection(node.Grid, botLeftX, topRightX, botLeftY, topRightY);
                Grid.SetSection(node.Room, Tile.Types.Floor, (obj) = > m_level.Floor.Add(obj));
                m_level.AddRoom(new Room(node.Room));
                break;
            }
        }
    }
}