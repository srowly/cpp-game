#include <vector>
#include "BSPParameters.h"
#include "Node.h"

#pragma once
class BSPAlgorithm
{
private:
	
public:
	Generate(Level level, BSPParameters parameters, int seed);
	DivideGrid(Grid grid, Node node);
};

