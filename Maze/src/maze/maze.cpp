#include "maze.h"

#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "../util/bitmap.h"

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
	FILE* f = fopen(str.c_str(), "rb");
	if(readSingleImageBMP(f, &image, &w, &h))
		return;
	width = static_cast<int>(w);
	height = static_cast<int>(h);
	tiles = new Tile[width * height];
	for (int i = 0; i < width * height; i++)
	{
		bool r = image[i].red && 0xFF;
		bool g = image[i].green && 0xFF;
		bool b = image[i].blue && 0xFF;

		if (!(r || g || b))
		{
			tiles[i] = Tile::WALL;
			walls.push_back(glm::vec3(x(i), 0, y(i)));
		}
		else if (r && g && b)
			tiles[i] = Tile::EMPTY;
		else if (!r && !g && b)
		{
			tiles[i] = Tile::ENTRY;
			entry = glm::vec3(x(i), 0, y(i));
		}
		else if (r && !g && !b)
		{
			tiles[i] = Tile::EXIT;
			exit = glm::vec3(x(i), 0, y(i));
		}
	}
	fclose(f);
	bind();
}

Maze::~Maze()
{
}

void Maze::bind()
{
	//cube.Bind();
}

void Maze::draw(Program* program)
{
	cube.bind();
	for (const glm::vec3 pos : walls)
	{
		glm::mat4 transform;
		glm::vec3 color(0.2f, 0.2f, 0.2f);
		transform = glm::scale(transform, size * glm::vec3(0.9999f, 0.9999f, 0.9999f));
		transform = glm::translate(transform, size * glm::vec3(pos));
		program->setMat4(transform, "transform");
		program->setVec3(color, "color");
		cube.draw();
	}

}

Tile * Maze::copyBoard()
{
	Tile* cpy = new Tile[width * height];
	std::memcpy(cpy, tiles, sizeof(Tile) * width * height);
	return cpy;
}

glm::vec3 Maze::getEntryPosition()
{
	return entry + glm::vec3(size / 2, PLAYER_HEIGHT, size / 2);
}

bool Maze::checkCollision(glm::vec3 current, glm::vec3& position)
{
	bool collide = false;
	int cur_x = static_cast<int>(floorf(current.x / size));
	int cur_y = static_cast<int>(floorf(current.z / size));

	int pos_x = static_cast<int>(floorf(position.x / size));
	int pos_y = static_cast<int>(floorf(position.z / size));

	if (pos_x - cur_x > 0 && tiles[i(cur_x + 1, cur_y)])
	{
		position.x = (cur_x + 1) * size - PLAYER_OFFSET;
		collide = true;
	}

	if (pos_x - cur_x < 0 && tiles[i(cur_x - 1, cur_y)])
	{
		position.x = (cur_x) * size + PLAYER_OFFSET;
		collide = true;
	}

	if (pos_y - cur_y > 0 && tiles[i(cur_x, cur_y + 1)])
	{
		position.z = (cur_y + 1) * size - PLAYER_OFFSET;
		collide = true;
	}

	if (pos_y - cur_y < 0 && tiles[i(cur_x, cur_y - 1)])
	{
		position.z = (cur_y) * size + PLAYER_OFFSET;
		collide = true;
	}


	return collide;
}
