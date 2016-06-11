#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "proceduralmaze.h"

ProceduralMaze::ProceduralMaze(int width, int height)
{
	std::srand(std::time(NULL));

	this->grid = std::map<std::tuple<int, int>, Tile>();
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

	std::vector<std::tuple<int, int>> frontiers = getAdjCells(cell_pos, Tile::WALL, 2);
	while (!frontiers.empty()) {
		int index = std::rand() % frontiers.size();
		cell_pos = frontiers[index];
		frontiers.erase(frontiers.begin() + index);

		std::vector<std::tuple<int, int>> neighboors = getAdjCells(cell_pos, Tile::EMPTY, 2);
		if (neighboors.empty()) {
			continue;
		}

		index = std::rand() % neighboors.size();
		std::tuple<int, int> neighboor = neighboors[index];
		int passage_x = (std::get<0>(neighboor) - std::get<0>(cell_pos))/2 + std::get<0>(cell_pos);
		int passage_y = (std::get<1>(neighboor) - std::get<1>(cell_pos))/2 + std::get<1>(cell_pos);

		grid[std::make_tuple(passage_x, passage_y)] = Tile::EMPTY;
		grid[cell_pos] = Tile::EMPTY;
		for (auto value : getAdjCells(cell_pos, Tile::WALL)), 2 {
			if (std::find(frontiers.begin(), frontiers.end(), value) == frontiers.end()) {
				frontiers.push_back(value);
			}
		}
	}

	std::tuple<int, int> entry_pos = std::make_tuple(1, 0);
	grid[entry_pos] = Tile::ENTRY;

	std::tuple<int, int> exit_pos = std::make_tuple(width - 2, height - 1);
	grid[exit_pos] = Tile::EXIT;

	generateLight();
}

void ProceduralMaze::generateLight() {

}

void ProceduralMaze::clearGrid()
{
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			grid[std::make_tuple(x, y)] = Tile::WALL;
		}
	}
}

std::vector<std::tuple<int,int>> ProceduralMaze::getAdjCells(std::tuple<int, int> center, Tile tile_state, int dist)
{
	std::vector<std::tuple<int, int>> pos = {
		std::make_tuple(std::get<0>(center) + dist, std::get<1>(center)),
		std::make_tuple(std::get<0>(center) - dist, std::get<1>(center)),
		std::make_tuple(std::get<0>(center), std::get<1>(center) + dist),
		std::make_tuple(std::get<0>(center), std::get<1>(center) - dist),
	};

	std::vector<std::tuple<int, int>> result = std::vector<std::tuple<int, int>>();
	for (auto adj_pos : pos) {
		try {
			switch (grid.at(adj_pos)) {
				case Tile::WALL:
					if (tile_state == Tile::WALL) { result.push_back(adj_pos); }
					break;
				case Tile::LIGHT:
				case Tile::EMPTY:
					if (tile_state != Tile::WALL) { result.push_back(adj_pos); }
					break;
				default:
					break;
			}
		} catch (std::out_of_range) { }
	}

	return result;
}

void ProceduralMaze::print() {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			char c = ' ';
			switch (grid[std::make_tuple(x, y)]) {
				case Tile::ENTRY:
					c = 'E';
					break;
				case Tile::EXIT:
					c = 'S';
					break;
				case Tile::WALL:
					c = '#';
					break;
				case Tile::LIGHT:
					c = ' ';
					break;
				default:
					break;
			}

			std::cout << c;
		}
		std::cout << std::endl;
	}
}

int main(void) {
	ProceduralMaze* maze = new ProceduralMaze(15, 15);
	maze->generate();
	maze->print();

	return 0;
}
