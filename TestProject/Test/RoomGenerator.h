#include "Vector2.h"
#include "Node.h"

#pragma once
class RoomGenerator
{
private:
    Vector2<int> minSize;
    Level level;

public:

    RoomGenerator(Level level, Vector2<int> minSize);
    void PlaceRooms(Node node);
    void GenNewRoom(Node node);
};