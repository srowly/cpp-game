
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
	BSPParameters params = { 10, 10, 10, CorridorType::Straight };
	BSPAlgorithm bsp = BSPAlgorithm();
	bsp.Run(grid, params, 100);
	RoomGenerator roomGen = RoomGenerator(2, 2, bsp);
	roomGen.PlaceRooms(bsp.root);
	setSection(bsp, bsp.root->grid, Tile::Types::Wall, 500);
	setSections(bsp, bsp.root, 600);
}

void Level::setSection(BSPAlgorithm &bsp, TileGrid grid, Tile::Types type, int spriteNo)
{
	std::function<void(Tile*)> lambda = [&, spriteNo](Tile* t) { renderer.renderSpriteFromSheet(spriteNo, t->gridPosition.x * 32, t->gridPosition.y * 32); };
	bsp.setSection(grid, type, lambda);
}

void Level::setSections(BSPAlgorithm& bsp, Node* node, int spriteNo)
{
	setSection(bsp, node->room, Tile::Types::Floor, spriteNo);
	if (node->rightChild != NULL)
		setSections(bsp, node->rightChild, spriteNo);
	if (node->leftChild != NULL)
		setSections(bsp, node->leftChild, spriteNo);
}
