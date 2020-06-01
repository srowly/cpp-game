#include "BSPAlgorithm.h"

void BSPAlgorithm::Generate(Level level, BSPParameters parameters, int seed)
{
    srand(seed);

    minNodeSize = { level.grid.tiles.size() / parameters.minNumRooms, level.grid.tiles[0].size() / parameters.minNumRooms };

    Node* root = new Node(level.grid.tiles);
    DivideGrid(level.grid, root);

    RoomGenerator roomGenerator = RoomGenerator(level, { parameters.minRoomWidth, parameters.minRoomHeight } );
    roomGenerator.PlaceRooms(root);

    CorridorGenerator corridorGenerator = CorridorGenerator(level, parameters.corridorType);
    corridorGenerator.PlaceCorridors(root);
    delete root;
}

void BSPAlgorithm::DivideGrid(Grid grid, Node* node)
{
    int splitPoint;

    int gridX = node->size.x;
    int gridY = node->size.y;

    if ((rand() % 2 + 1) == 2)
    {
        splitPoint = rand() % gridX - minNodeSize.x + minNodeSize.x;
        node->leftChild = new Node(grid.GetSection(node->grid.tiles, 0, splitPoint, 0, gridY));
        node->rightChild = new Node(grid.GetSection(node->grid.tiles, splitPoint, gridX, 0, gridY));
    }

    else
    {
        splitPoint = rand() % gridY - minNodeSize.y + minNodeSize.y;
        node->leftChild = new Node(grid.GetSection(node->grid.tiles, 0, gridX, 0, splitPoint));
        node->rightChild = new Node(grid.GetSection(node->grid.tiles, 0, gridX, splitPoint, gridY));
    }

    if (node->leftChild->size.x > minNodeSize.x && node->leftChild->size.y > minNodeSize.y)
    {
        DivideGrid(grid, node->leftChild);
    }
    if (node->rightChild->size.x > minNodeSize.x && node->rightChild->size.y > minNodeSize.y)
    {
        DivideGrid(grid, node->rightChild);
    }
}