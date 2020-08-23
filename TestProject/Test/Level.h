#include <unordered_set>

#include "BSPAlgorithm.h"
#include "Renderer.h"
#include "RoomGenerator.h"
#include <time.h>
#include <list>

#pragma once
class Level
{
public:
	TileGrid grid;

	Renderer& renderer;

    Level(Renderer& renderer);

	void generateWithBSP();
private:
	void setSection(BSPAlgorithm& bsp, TileGrid grid, Tile::Types type, int spriteNo);
};

