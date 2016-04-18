#pragma once

#include <cstring>

enum Tile
{
	EMPTY,
	WALL,
	ENTRY,
	EXIT,
	VISITED,
	UNVISITED
};

class Maze
{
	int width, height;
	Tile* tiles;

	size_t i(size_t x, size_t y)
	{
		return y * width + x;
	}
public:
	Maze(int width, int height);
	~Maze();
	Tile* copyBoard();
};

