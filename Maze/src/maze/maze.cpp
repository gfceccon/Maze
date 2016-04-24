#include "maze.h"

#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include "../util/bitmap.h"
#include "../util/log.h"

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
	FILE* f;
#ifdef _MSC_VER 
	fopen_s(&f, str.c_str(), "rb");
#else
	f = fopen(str.c_str(), "rb");
#endif
	if (!f) {
		throw std::runtime_error("File " + str + " does not exist");
	}

	if (readSingleImageBMP(f, &image, &w, &h)) {
		return;
	}

	width = static_cast<int>(w);
	height = static_cast<int>(h);
	tiles = new Tile[width * height];
	for (int i = 0; i < width * height; i++) {
		bool r = image[i].red && 0xFF;
		bool g = image[i].green && 0xFF;
		bool b = image[i].blue && 0xFF;

		if (!(r || g || b)) {
			tiles[i] = Tile::WALL;
			walls.push_back(glm::vec3(x(i), 0, y(i)));
		} else if (r && g && b) {
			tiles[i] = Tile::EMPTY;
		} else if (!r && !g && b) {
			tiles[i] = Tile::ENTRY;
			entry = glm::vec3(x(i), 0, y(i));
		} else if (r && !g && !b) {
			tiles[i] = Tile::EXIT;
			exit = glm::vec3(x(i), 0, y(i));
		}
	}
	fclose(f);

	cube = new Cube();
}

Maze::~Maze()
{
}

void Maze::bind()
{
	cube->bind();
}

void Maze::drawSingle()
{
	cube->draw();
}

void Maze::draw(Program* program)
{
	this->bind();
	for (const glm::vec3 pos : walls) {
		glm::mat4 transform;
		glm::vec3 color(0.2f, 0.2f, 0.2f);
		transform = glm::scale(transform, size * glm::vec3(0.9999f, 0.9999f, 0.9999f));
		transform = glm::translate(transform, size * glm::vec3(pos));
		program->setMat4(transform, "transform");
		program->setVec3(color, "color");
		this->drawSingle();
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

inline float max(float x, float y)
{
	return x > y ? x : y;
}

bool Maze::checkCollision(glm::vec3 current, glm::vec3& position)
{
	int cur_x = static_cast<int>(floorf(current.x / size));
	int cur_z = static_cast<int>(floorf(current.z / size));

	int pos_x = cur_x, pos_z = cur_z;

	glm::vec3 direction = position - current;

	Direction dir_x = Direction::UNKNOW, dir_z = Direction::UNKNOW;

	if (direction.x > 0) {
		dir_x = Direction::EAST;
		pos_x = static_cast<int>(floorf((position.x + PLAYER_OFFSET) / size));
	}
	if (direction.x < 0) {
		dir_x = Direction::WEST;
		pos_x = static_cast<int>(floorf((position.x - PLAYER_OFFSET) / size));
	}
	if (direction.z > 0) {
		dir_z = Direction::NORTH;
		pos_z = static_cast<int>(floorf((position.z + PLAYER_OFFSET) / size));
	}
	if (direction.z < 0) {
		dir_z = Direction::SOUTH;
		pos_z = static_cast<int>(floorf((position.z - PLAYER_OFFSET) / size));
	}

	if (dir_x == Direction::UNKNOW && dir_z == Direction::UNKNOW) {
		return false;
	}

	bool collide = false;

	float x1 = size, z1 = size;
	float x2 = size, z2 = size;

	if (dir_x == Direction::EAST && pos_x - cur_x > 0 && tiles[i(cur_x + 1, cur_z)]) {
		x1 = ((cur_x + 1) * size - PLAYER_OFFSET * RESPONSE) - current.x;
		z1 = ((position.z - current.z) * x1) / max (position.x - current.x, MIN_RESPONSE);
		collide = true;
	} else if (dir_x == Direction::WEST && pos_x - cur_x < 0 && tiles[i(cur_x - 1, cur_z)]) {
		x1 = ((cur_x) * size + PLAYER_OFFSET * RESPONSE) - current.x;
		z1 = (x1 * (position.z - current.z)) / max (position.x - current.x, MIN_RESPONSE);
		collide = true;
	}

	if (dir_z == Direction::NORTH && pos_z - cur_z > 0 && tiles[i(cur_x, cur_z + 1)]) {
		z2 = ((cur_z + 1) * size - PLAYER_OFFSET * RESPONSE) - current.z;
		x2 = (z2 * (position.x - current.x)) / max (position.z - current.z, MIN_RESPONSE);
		collide = true;
	} else if (dir_z == Direction::SOUTH && pos_z - cur_z < 0 && tiles[i(cur_x, cur_z - 1)]) {
		z2 = ((cur_z) * size + PLAYER_OFFSET * RESPONSE) - current.z;
		x2 = (z2 * (position.x - current.x)) / max (position.z - current.z, MIN_RESPONSE);
		collide = true;
	}

	if (!collide) {
		return collide;
	}

	if (x1 * x1 + z1 * z1 < x2 * x2 + z2 * z2) {
		position = current + glm::vec3(x1, 0, z1);
	} else {
		position = current + glm::vec3(x2, 0, z2);
	}

	return collide;
}
