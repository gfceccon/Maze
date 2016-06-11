#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "proceduralmaze.h"

ProceduralMaze::ProceduralMaze(int width, int height)
{
	std::srand(std::time(NULL));

	this->width = width % 2 == 0 ? width + 1 : width;
	this->height = height % 2 == 0 ? height + 1 : height;

	clearGrid();
}

void ProceduralMaze::generate()
{
	clearGrid();
	int x = std::rand() % (width - 2) + 1;
	int y = std::rand() % (height - 2) + 1;

	// Odd start numbers to make sure we have borders
	x = x % 2 == 0 ? x + 1 : x;
	y = y % 2 == 0 ? y + 1 : y;

	std::pair<int, int> cell_pos = std::make_pair(x, y);
	grid[cell_pos] = Tile::EMPTY;

	std::vector<std::pair<int, int>> frontiers = getAdjCells(cell_pos, Tile::WALL, 2);
	while (!frontiers.empty()) {
		int index = std::rand() % frontiers.size();
		cell_pos = frontiers[index];
		frontiers.erase(frontiers.begin() + index);

		std::vector<std::pair<int, int>> neighboors = getAdjCells(cell_pos, Tile::EMPTY, 2);
		if (neighboors.empty()) {
			continue;
		}

		index = std::rand() % neighboors.size();
		std::pair<int, int> neighboor = neighboors[index];
		int passage_x = (neighboor.first - cell_pos.first)/2 + cell_pos.first;
		int passage_y = (neighboor.second - cell_pos.second)/2 + cell_pos.second;

		grid[std::make_pair(passage_x, passage_y)] = Tile::EMPTY;
		grid[cell_pos] = Tile::EMPTY;
		for (auto value : getAdjCells(cell_pos, Tile::WALL, 2)) {
			if (std::find(frontiers.begin(), frontiers.end(), value) == frontiers.end()) {
				frontiers.push_back(value);
			}
		}
	}

	std::pair<int, int> entry_pos = std::make_pair(1, 0);
	grid[entry_pos] = Tile::ENTRY;

	std::pair<int, int> exit_pos = std::make_pair(width - 2, height - 1);
	grid[exit_pos] = Tile::EXIT;

	generateLight();
}

void ProceduralMaze::generateLight() {
	std::vector<std::pair<int, int>> check_stack;
	std::vector<std::pair<int, int>> visited_cells;
	std::vector<std::pair<int, int>> illuminated_cells;

	check_stack.push_back(std::make_pair(1, 1));
	int steps = 0;

	while (!check_stack.empty()) {
		std::pair<int, int> check_pos = check_stack.back();
		check_stack.pop_back();

		visited_cells.push_back(check_pos);

		auto neighboors = getAdjCells(check_pos, Tile::EMPTY, 1);
		for (auto n_pos : neighboors) {
			if (std::find(visited_cells.begin(), visited_cells.end(), n_pos) == visited_cells.end()) {
				check_stack.push_back(n_pos);
			}
		}

		steps++;
		if (steps < 4) {
			continue;
		}

		if (std::find(illuminated_cells.begin(), illuminated_cells.end(), check_pos) == illuminated_cells.end()) {
			auto diag_cells = getDiagCells(check_pos);
			neighboors.insert(neighboors.end(), diag_cells.begin(), diag_cells.end());

			auto far_neighboors = getAdjCells(check_pos, Tile::EMPTY, 2);
			for (auto it = far_neighboors.rbegin(); it != far_neighboors.rend(); ++it) {
				int passage_x = ((*it).first - check_pos.first)/2 + check_pos.first;
				int passage_y = ((*it).second - check_pos.second)/2 + check_pos.second;
				std::pair<int, int> passage = std::make_pair(passage_x, passage_y);

				if (std::find(neighboors.begin(), neighboors.end(), passage) != neighboors.end()) {
					neighboors.push_back(*it);
				}
			}

			bool intersect_illuminated_cell = false;
			for (auto neighboor : neighboors) {
				if (std::find(illuminated_cells.begin(), illuminated_cells.end(), neighboor) != illuminated_cells.end()) {
					intersect_illuminated_cell = true;
				}
			}

			if (intersect_illuminated_cell) {
				continue;
			}

			grid[check_pos] = Tile::LIGHT;
			illuminated_cells.insert(illuminated_cells.end(), neighboors.begin(), neighboors.end());
			illuminated_cells.push_back(check_pos);

			steps = 0;
		}
	}
}

void ProceduralMaze::clearGrid()
{
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			grid[std::make_pair(x, y)] = Tile::WALL;
		}
	}
}

std::vector<std::pair<int, int>> ProceduralMaze::getDiagCells(std::pair<int, int> center) {
	std::vector<std::pair<int, int>> neighboors;
	for (int x = -1; x <= 1; x = x + 2) {
		for (int y = -1; y <= 1; y = y + 2) {
			try {
				std::pair<int, int> n_cell = std::make_pair(center.first + x, center.second + y);
				if (grid.at(n_cell) == Tile::EMPTY) {
					neighboors.push_back(n_cell);
				}
			} catch (std::out_of_range) {}
		}
	}

	return neighboors;
}

std::vector<std::pair<int, int>> ProceduralMaze::getAdjCells(std::pair<int, int> center, Tile tile_state, int dist)
{
	const std::vector<std::pair<int, int>>& pos = {
		std::make_pair(center.first, center.second - dist),
		std::make_pair(center.first + dist, center.second),
		std::make_pair(center.first, center.second + dist),
		std::make_pair(center.first - dist, center.second),
	};

	std::vector<std::pair<int, int>> result;
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
			switch (grid[std::make_pair(x, y)]) {
				case Tile::ENTRY:
					c = 'E';
					break;
				case Tile::EXIT:
					c = 'S';
					break;
				case Tile::WALL:
					c = '#';
					break;
				case Tile::EMPTY:
					c = ' ';
					break;
				case Tile::LIGHT:
					c = '.';
					break;
				default:
					break;
			}

			std::cout << c;
		}
		std::cout << std::endl;
	}
}
