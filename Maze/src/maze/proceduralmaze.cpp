#include <iostream>
#include "proceduralmaze.h"

ProceduralMaze::ProceduralMaze(int width, int height)
{
	this->height = height % 2 == 0 ? height + 1 : height;
	this->width = width % 2 == 0 ? width + 1 : width;

	this->grid = std::map<std::tuple<int, int>, int>();
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			this->grid[std::make_tuple(x, y)] = Tile::WALL;
		}
	}
}

int main(void)
{
	ProceduralMaze* maze = new ProceduralMaze(10, 10);
	std::cout << maze->grid[std::make_tuple(5, 5)] << std::endl;

	return 0;
}