#ifndef __PROCEDURALMAZE_H__
#define __PROCEDURALMAZE_H__

#include "maze.h"
#include <map>

class ProceduralMaze
{
	private:
		int width;
		int height;

	public:
		std::map<std::tuple<int, int>, int> grid;
		ProceduralMaze(int width, int height);

		void generate();
		void clear_grid();
		std::vector<std::tuple<int, int>> getAdjCells(std::tuple<int, int> center, Tile tile_state);
};

#endif