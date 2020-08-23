#include <functional>
#include <vector>

#include "Vector2.h"

#pragma once
class Tile
{
public:
    
    enum class Types
    {
        Wall,
        Floor,
    };

    Types type; 
    Vector2<int> gridPosition;

    bool operator==(const Tile& t) const;

    Tile(Types type, Vector2<int> gridPos);

};

using TileGrid = std::vector<std::vector<Tile*> >;

namespace std 
{
    template <> struct hash<Tile> 
    {
        size_t operator()(const Tile& x) const 
        {
            std::hash<int> i;
            return i(x.gridPosition.x) + i(x.gridPosition.y);
        }
    };
}
