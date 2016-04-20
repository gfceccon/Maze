#pragma once

#include "maze.h"
#include <vector>
#include <queue>
#include <glm/vec2.hpp>


class Path
{
public:
	Path();
	~Path();
	static Path getClosestPath(Maze* maze, glm::ivec2 begin, glm::ivec2 end);
};

