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
public:
	Maze(int width, int height);
	~Maze();
	Tile* copyBoard();
};

