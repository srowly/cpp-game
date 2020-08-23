#include "Tile.h"

Tile::Tile(Types type, Vector2<int> gridPos) : type(type), gridPosition(gridPos)
{

}

bool Tile::operator==(const Tile& t) const
{
    return this == &t && this->gridPosition.x == t.gridPosition.x &&
        this->gridPosition.y == t.gridPosition.y;
}
