#include <iostream>
#include "proceduralmaze.h"

ProceduralMaze::ProceduralMaze(int width, int height)
{
	this->height = height % 2 == 0 ? height + 1 : height;
	this->width = width % 2 == 0 ? width + 1 : width;

	this->grid = std::map<std::tuple<int, int>, int>();
	clearGrid();
}

void ProceduralMaze::generate()
{
	clearGrid();
	/*
	let x = rand::thread_rng().gen_range(1, self.width - 1);
	let y = rand::thread_rng().gen_range(1, self.height - 1);

	let x = if x % 2 == 0 { x + 1} else { x };
	let y = if y % 2 == 0 { y + 1} else { y };

	// First frontier cell needs to be odd to guarantee borders
	let cell = CellPos(x, y);
	{
		let entry = self.grid.get_mut(&cell).unwrap();
		*entry = CellState::PASSAGE;
	}

	let mut frontiers = self.get_adjcells(cell, CellState::BLOCKED);
	while !frontiers.is_empty() {
		let index = rand::thread_rng().gen_range(0, frontiers.len());
		let cell = frontiers.swap_remove(index);
		let neighboors = self.get_adjcells(cell, CellState::PASSAGE);

		if neighboors.len() == 0 {
			continue;
		}

		let index = rand::thread_rng().gen_range(0, neighboors.len());
		let neighboor = neighboors.get(index).unwrap();
		let passage = cell - *neighboor;
		{
			let entry = self.grid.get_mut(&passage).unwrap();
			*entry = CellState::PASSAGE;
		}
		{
			let entry = self.grid.get_mut(&cell).unwrap();
			*entry = CellState::PASSAGE;
		}

		let v: Vec<CellPos> = self.get_adjcells(cell, CellState::BLOCKED)
									.into_iter()
									.filter(|value| !frontiers.contains(value))
									.collect();
		frontiers.extend(v.into_iter());
	}*/
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
		if (grid[adj_pos] == tile_state) {
			result.push_back(adj_pos);
		}
	}

	return result;
}

int main(void)
{
	ProceduralMaze* maze = new ProceduralMaze(10, 10);
	std::cout << maze->grid[std::make_tuple(5, 5)] << std::endl;

	return 0;
}