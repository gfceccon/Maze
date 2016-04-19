#include "maze.h"

#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include <util/bitmap.h>

Maze::Maze(int width, int height, float size) : width(width), height(height), size(size)
{
	tiles = new Tile[width * height];
	Bind();
}

Maze::Maze(const char* bmp, float size) : size(size)
{
	std::string str(path);
	str += bmp;

	RGB* image;
	UINT32 w, h;
	FILE* file = fopen(str.c_str(), "rb");
	if(readSingleImageBMP(file, &image, &w, &h))
		return;
	width = static_cast<int>(w);
	height = static_cast<int>(h);
	tiles = new Tile[width * height];
	for (size_t i = 0; i < width * height; i++)
	{
		bool r = image[i].red & 0xFF;
		bool g = image[i].green & 0xFF;
		bool b = image[i].blue & 0xFF;

		if (!(r || g || b))
		{
			tiles[i] = Tile::WALL;
			walls.push_back(glm::ivec3(x(i) - width / 2, 0, y(i) - height / 2));
		}
		else if (r && g && b)
			tiles[i] = Tile::EMPTY;
		else if (!r && !g && b)
			tiles[i] = Tile::ENTRY;
		else if (r && !g && !b)
			tiles[i] = Tile::EXIT;
	}
	Bind();
}

Maze::~Maze()
{
}

void Maze::Bind()
{
	//cube.Bind();
}

void Maze::Draw(Program* program)
{
	cube.Bind();
	srand(time(NULL));
	for (const glm::ivec3 pos : walls)
	{
		glm::mat4 transform;
		glm::vec3 color((float)rand() / (float) RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
		transform = glm::translate(transform, size * glm::vec3(pos));
		transform = glm::scale(transform, size * glm::vec3(0.999f, 0.999f, 0.999f));
		program->SetMat4(transform, "transform");
		program->SetVec3(color, "color");
		cube.Draw();
	}
	
}

Tile * Maze::CopyBoard()
{
	Tile* cpy = new Tile[width * height];
	std::memcpy(cpy, tiles, sizeof(Tile) * width * height);
	return cpy;
}
