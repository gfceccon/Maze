#pragma once

#include <util/vector2i.h>
#include <maze/maze.h>
#include <vector>
#include <queue>


class Path
{
	std::vector<Vector2i> path;
public:
	Path();
	~Path();
	static Path getClosestPath(Maze* maze, Vector2i begin, Vector2i end);
};

