#include "maze.h"

Maze::Maze(int width, int height)
{
}

Maze::~Maze()
{
}

Tile * Maze::copyBoard()
{
	Tile* cpy = new Tile[width * height];
	std::memcpy(cpy, tiles, sizeof(Tile) * width * height);
	return cpy;
}
