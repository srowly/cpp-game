
#include "Level.h"

Level::Level(Renderer& renderer) : renderer(renderer)
{
	TileGrid tiles;

	for (int i = 0; i < 50; i++)
	{
		std::vector<Tile*> v1;

		for (int j = 0; j < 30; j++)
		{
			Tile* tile = new Tile(Tile::Types::Floor, Vector2<int>(i, j));
			v1.push_back(tile);
		}

		tiles.push_back(v1);
	}

	grid = tiles;
}

void Level::generateWithBSP()
{
	BSPAlgorithm bsp = BSPAlgorithm(grid, time(NULL));
	bsp.Run();

	setSection(bsp, bsp.root->grid, Tile::Types::Wall, 702);

	RoomGenerator roomGen = RoomGenerator(4, 4, bsp);
	roomGen.PlaceRooms(bsp.root);

	CorridorGenerator corridorGen = CorridorGenerator(bsp);
	corridorGen.PlaceCorridors(bsp.root);

	std::vector<TileGrid>::iterator corridors;

	for (corridors = corridorGen.corridors.begin(); corridors != corridorGen.corridors.end(); ++corridors)
	{
		setSection(bsp, (*corridors), Tile::Types::Floor, 400);
	}

	std::function<void(Node*)> lambda2 = [&](Node* n) { setSection(bsp, n->room, Tile::Types::Floor, 400); };
	bsp.forAllNodes(lambda2);

	printf("BSP Finished");
}

void Level::setSection(BSPAlgorithm &bsp, TileGrid grid, Tile::Types type, int spriteNo)
{
	std::function<void(Tile*)> lambda = [&, spriteNo](Tile* t) { renderer.renderSpriteFromSheet(spriteNo, t->gridPosition.x * 32, t->gridPosition.y * 32); };
	bsp.setSection(grid, type, lambda);
}