#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "proceduralmaze.h"

ProceduralMaze::ProceduralMaze(int width, int height)
{
	std::srand(std::time(NULL));

	// Odd width and height to make sure we have borders
	this->height = height % 2 == 0 ? height + 1 : height;
	this->width = width % 2 == 0 ? width + 1 : width;

	this->grid = std::map<std::tuple<int, int>, int>();
	clearGrid();
}

void ProceduralMaze::generate()
{
	clearGrid();
	int x = std::rand() % (width - 1) + 1;
	int y = std::rand() % (height - 1) + 1;

	// Odd start numbers to make sure we have borders
	x = x % 2 == 0 ? x + 1 : x;
	y = y % 2 == 0 ? y + 1 : y;

	std::tuple<int, int> cell_pos = std::make_tuple(x, y);
	grid[cell_pos] = Tile::EMPTY;

	std::vector<std::tuple<int, int>> frontiers = getAdjCells(cell_pos, Tile::WALL);
	while (!frontiers.empty()) {
		int index = std::rand() % frontiers.size();
		cell_pos = frontiers[index];
		frontiers.erase(frontiers.begin() + index);

		std::vector<std::tuple<int, int>> neighboors = getAdjCells(cell_pos, Tile::EMPTY);
		if (neighboors.empty()) {
			continue;
		}

		index = std::rand() % neighboors.size();
		std::tuple<int, int> neighboor = neighboors[index];
		int passage_x = (std::get<0>(neighboor) - std::get<0>(cell_pos))/2 + std::get<0>(cell_pos);
		int passage_y = (std::get<1>(neighboor) - std::get<1>(cell_pos))/2 + std::get<1>(cell_pos);

		grid[std::make_tuple(passage_x, passage_y)] = Tile::EMPTY;
		grid[cell_pos] = Tile::EMPTY;
		for (auto value : getAdjCells(cell_pos, Tile::WALL)) {
			if (std::find(frontiers.begin(), frontiers.end(), value) == frontiers.end()) {
				frontiers.push_back(value);
			}
		}
	}
}

void ProceduralMaze::clearGrid()
{
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			grid[std::make_tuple(x, y)] = Tile::WALL;
		}
	}
}

std::vector<std::tuple<int,int>> ProceduralMaze::getAdjCells(std::tuple<int, int> center, Tile tile_state)
{
	std::vector<std::tuple<int, int>> pos = {
		std::make_tuple(std::get<0>(center) + 2, std::get<1>(center)),
		std::make_tuple(std::get<0>(center) - 2, std::get<1>(center)),
		std::make_tuple(std::get<0>(center), std::get<1>(center) + 2),
		std::make_tuple(std::get<0>(center), std::get<1>(center) - 2),
	};

	std::vector<std::tuple<int, int>> result = std::vector<std::tuple<int, int>>();
	for (auto adj_pos : pos) {
		try {
			if (grid.at(adj_pos) == tile_state) {
				result.push_back(adj_pos);
			}
		} catch (std::out_of_range) {}
	}

	return result;
}

void ProceduralMaze::print() {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			char c = grid[std::make_tuple(x, y)] == Tile::EMPTY ? '.' : '#';
			std::cout << c;
		}
		std::cout << std::endl;
	}
}

int main(void)
{
	ProceduralMaze* maze = new ProceduralMaze(11, 11);
	maze->generate();
	maze->print();

	return 0;
}