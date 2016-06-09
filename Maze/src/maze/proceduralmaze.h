#ifndef __PROCEDURALMAZE_H__
#define __PROCEDURALMAZE_H__

#include "maze.h"
#include <map>

class ProceduralMaze
{
	private:
		int width;
		int height;
		std::map<std::tuple<int, int>, int> grid;

		void clearGrid();
		std::vector<std::tuple<int, int>> getAdjCells(std::tuple<int, int> center, Tile tile_state);

	public:
		ProceduralMaze(int width, int height);

		void generate();
		void print();
		std::map<std::tuple<int, int>, int> getGrid() { return grid; }
};

#endif