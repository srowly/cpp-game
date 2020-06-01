#include "RoomGenerator.h"


RoomGenerator::RoomGenerator(Level level, Vector2<int> minSize)
{
    this->minSize = minSize;
    this->level = level;
}

void RoomGenerator::PlaceRooms(Node* node)
{
    if (node->leftChild == NULL && node->rightChild == NULL)
    {
        GenNewRoom(node);
    }
    else
    {
        PlaceRooms(node->leftChild);
        PlaceRooms(node->rightChild);
    }
}

void RoomGenerator::GenNewRoom(Node* node)
{
    int nodeX = node->size.x;
    int nodeY = node->size.y;

    for (int i = 0; i < 50; i++)
    {
        int botLeftX = rand() % nodeX / 2 + 1;
        int botLeftY = rand() % nodeY / 2 + 1;
        int topRightX = rand() % nodeX + nodeX / 2; 
        int topRightY = rand() % nodeY + nodeY / 2;

        int width = topRightX - botLeftX;
        int height = topRightY - botLeftY;

        float maxWidth = nodeX;
        float maxHeight = nodeY;

        int varyRoom = rand() % 3 + 1;
        if (varyRoom == 1)
        {
            maxWidth = round(maxWidth / 2);
            maxHeight = round(maxHeight / 2);
        }

        if (varyRoom == 2)
        {
            maxWidth = round(maxWidth / 1.5f);
            maxHeight = round(maxHeight / 1.5f);
        }

        if ((width > minSize.x) && (height > minSize.y))
        {
            if ((width < maxWidth) && (height < maxHeight))
            {
                node->room = Grid::GetSection(node->grid.tiles, botLeftX, topRightX, botLeftY, topRightY);

                std::function<void(Tile)> lambda = [&](Tile t) { level.floor.insert(t); };
                Grid::SetSection(node->room.tiles, Tile::Types::Floor, lambda);
                level.AddRoom(node->room.tiles);
                break;
            }
        }
    }
}