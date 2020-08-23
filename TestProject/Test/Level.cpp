
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
	BSPAlgorithm bsp = BSPAlgorithm();
	bsp.Run(grid, time(NULL));

	setSection(bsp, bsp.root->grid, Tile::Types::Wall, 702);

	RoomGenerator roomGen = RoomGenerator(4, 4, bsp);
	roomGen.PlaceRooms(bsp.root);

	std::function<void(Node*)> lambda = [&] (Node* n) { setSection(bsp, n->grid, Tile::Types::Floor,1000); };
	bsp.forAllNodes(lambda);

	std::function<void(Node*)> lambda2 = [&](Node* n) { setSection(bsp, n->room, Tile::Types::Floor, 400); };
	bsp.forAllNodes(lambda2);

	printf("BSP Finished");
}

void Level::setSection(BSPAlgorithm &bsp, TileGrid grid, Tile::Types type, int spriteNo)
{
	std::function<void(Tile*)> lambda = [&, spriteNo](Tile* t) { renderer.renderSpriteFromSheet(spriteNo, t->gridPosition.x * 32, t->gridPosition.y * 32); };
	bsp.setSection(grid, type, lambda);
}