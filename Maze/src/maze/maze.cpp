#include "maze.h"

#include <cstdio>
#include <string>
#include <sstream>

#include <util/bitmap.h>

Maze::Maze(int width, int height, float size) : width(width), height(height), size(size)
{
	tiles = new Tile[width * height];
	bind();
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
			walls.push_back(glm::ivec3(x(i), y(i), 0));
		}
		else if (r && g && b)
			tiles[i] = Tile::EMPTY;
		else if (!r && !g && b)
		{
			tiles[i] = Tile::ENTRY;
			entry = glm::ivec3(x(i), y(i), 0);
		}
		else if (r && !g && !b)
		{
			tiles[i] = Tile::EXIT;
			exit = glm::ivec3(x(i), y(i), 0);
		}
	}
	bind();
}

Maze::~Maze()
{
}

void Maze::bind()
{
	cube.bind();
}

void Maze::draw(Program* program)
{
	cube.bind();
	for (const glm::ivec3 pos : walls)
	{
		glm::mat4 transform;
		transform = glm::translate(transform, size * glm::vec3(pos));
		transform = glm::scale(transform, size * glm::vec3(1.0f, 1.0f, 1.0f));
		program->setMat4(transform, "transform");
		cube.draw();
	}
	
}

Tile * Maze::copyBoard()
{
	Tile* cpy = new Tile[width * height];
	std::memcpy(cpy, tiles, sizeof(Tile) * width * height);
	return cpy;
}
