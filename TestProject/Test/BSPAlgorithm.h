#include <vector>
#include <stdlib.h>  

#include "BSPParameters.h"
#include "Node.h"
#include "Vector2.h"
#include "Level.h"
#include "RoomGenerator.h"
#include "CorridorGenerator.h"

#pragma once
class BSPAlgorithm
{
private:
	Vector2<int> minNodeSize;
public:
	void Generate(Level level, BSPParameters parameters, int seed);
	void DivideGrid(Grid grid, Node* node);
};