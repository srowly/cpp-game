#include "BSPAlgorithm.h"

BSPAlgorithm::BSPAlgorithm(TileGrid& grid, int seed) : minNodeSize(0, 0), grid(grid)
{
    root = NULL;
    srand(seed);
}

void BSPAlgorithm::Run()
{
    this->grid = grid;
    minNodeSize = { 5, 5 };
    root = new Node(grid, numNodes);
    nodes.push_back(root);
    DivideGrid(*root);
}

BSPAlgorithm::~BSPAlgorithm()
{
    if (root != NULL)
        delete root;
}

void BSPAlgorithm::DivideGrid(Node& node)
{
    int splitPoint;
    TileGrid grid = node.grid;
    int gridX = node.size.x;
    int gridY = node.size.y;
    TileGrid sectionX = {};
    TileGrid sectionY = {};

    if (rand() % (2) == 0)
    {
        splitPoint = rand() % ((gridX - minNodeSize.x)) + minNodeSize.x;
        sectionX = getSection(grid, 0, splitPoint, 0, gridY);
        sectionY = getSection(grid, splitPoint, gridX, 0, gridY);
    }
    else
    {
        splitPoint = rand() % ((gridY - minNodeSize.y)) + minNodeSize.y;
        sectionX = getSection(grid, 0, gridX, 0, splitPoint);
        sectionY = getSection(grid, 0, gridX, splitPoint, gridY);
    }
  
    if (sectionX.size() > minNodeSize.x && sectionX[0].size() > minNodeSize.y)
    {
        node.leftChild = new Node(sectionX, ++numNodes);
        nodes.push_back(node.leftChild);
        DivideGrid(*node.leftChild);
    }
    if (sectionY.size() > minNodeSize.x && sectionY[0].size() > minNodeSize.y)
    {
        node.rightChild = new Node(sectionY, ++numNodes);
        nodes.push_back(node.rightChild);
        DivideGrid(*node.rightChild);
    }
}

TileGrid BSPAlgorithm::getSection(TileGrid parentGrid, int minX, int maxX, int minY, int maxY)
{
    printf("\nbsp get section");
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
    printf("\nbsp get section finished");
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


void BSPAlgorithm::forAllNodes(std::function<void(Node*)> onNode)
{
    std::list <Node*> ::iterator it;
    int i = 0;
    for (it = nodes.begin(); it != nodes.end(); ++it)
    {
        printf("\nNode:%d Size:%d\n", i++, (*it)->size.x * (*it)->size.y);
        onNode((*it));
    }
}