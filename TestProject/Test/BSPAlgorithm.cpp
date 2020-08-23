#include "BSPAlgorithm.h"

BSPAlgorithm::BSPAlgorithm() : minNodeSize(0, 0)
{
}

void BSPAlgorithm::Run(TileGrid& grid, BSPParameters parameters, int seed)
{
    srand(seed);
    minNodeSize = { (int)grid.size() / parameters.minNumRooms, (int)grid[0].size() / parameters.minNumRooms };
    root = new Node(grid, numNodes);
    DivideGrid(grid, *root);
}

BSPAlgorithm::~BSPAlgorithm()
{
    if (root != NULL)
        delete root;
}

void BSPAlgorithm::DivideGrid(TileGrid& grid, Node& node)
{
    printf("\nNumNodes: %d", numNodes);
    int splitPoint;

    int gridX = node.size.x;
    int gridY = node.size.y;
    TileGrid sectionX = {};
    TileGrid sectionY = {};

    if (rand() % (2) == 0)
    {
        splitPoint = rand() % (gridX - minNodeSize.x) + minNodeSize.x;
        sectionX = getSection(grid, 0, splitPoint, 0, gridY);
        sectionY = getSection(grid, splitPoint, gridX, 0, gridY);
    }
    else
    {
        splitPoint = rand() % (gridY - minNodeSize.y) + minNodeSize.y;
        sectionX = getSection(grid, 0, gridX, 0, splitPoint);
        sectionY = getSection(grid, 0, gridX, splitPoint, gridY);
    }

    node.leftChild = new Node(sectionX, ++numNodes);
    node.rightChild = new Node(sectionY, ++numNodes);

    if (node.leftChild->size.x > minNodeSize.x && node.leftChild->size.y > minNodeSize.y)
    {
        DivideGrid(node.grid, *node.leftChild);
    }
    if (node.rightChild->size.x > minNodeSize.x && node.rightChild->size.y > minNodeSize.y)
    {
        DivideGrid(node.grid, *node.rightChild);
    }
}

TileGrid BSPAlgorithm::getSection(TileGrid parentGrid, int minX, int maxX, int minY, int maxY)
{
    TileGrid tiles;

    for (int i = minX; i < maxX; i++)
    {
        std::vector<Tile*> v1;

        for (int j = minY; j < maxY; j++)
        {
            v1.push_back(parentGrid[i][j]);
        }

        tiles.push_back(v1);
    }

    return tiles;
}

void BSPAlgorithm::setSection(TileGrid tiles, Tile::Types type, std::function<void(Tile*)> optionalOnSet)
{
    std::vector< std::vector<Tile*> >::iterator row;
    std::vector<Tile*>::iterator col;

    for (row = tiles.begin(); row != tiles.end(); ++row)
    {
        for (col = row->begin(); col != row->end(); ++col)
        {
            (*col)->type = type;

            if (optionalOnSet)
            {
                optionalOnSet(*col);
            }
        }
    }
}