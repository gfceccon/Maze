#pragma once

#include <maze/maze.h>
#include <vector>
#include <queue>
#include <vec2.hpp>


class Path
{
public:
	Path();
	~Path();
	static Path GetClosestPath(Maze* maze, glm::ivec2 begin, glm::ivec2 end);
};

