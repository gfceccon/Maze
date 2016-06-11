#include "maze.h"
#include "proceduralmaze.h"

#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include "../util/bitmap.h"
#include "../util/log.h"

Maze::Maze(int width, int height, float size) : size(size)
{
	this->height = height % 2 == 0 ? height + 1 : height;
	this->width = width % 2 == 0 ? width + 1 : width;
	ProceduralMaze* procedural_maze = new ProceduralMaze(this->width, this->height);
	procedural_maze->generate();

	std::map<std::tuple<int, int>, Tile> grid = procedural_maze->getGrid();
	this->tiles = new Tile[this->height * this->width];
	for (int x = 0; x < this->width; ++x) {
		for (int y = 0; y < this->height; ++y) {
			std::tuple<int, int> pos = std::make_tuple(x, y);
			this->tiles[x + this->width*y] = grid[pos];
		}
	}

	procedural_maze->print();
}

Maze::Maze(const char* bmp, float size) : size(size)
{
	std::string str(path);
	str += bmp;

	RGB* image;
	UINT32 w, h;
	FILE* f = fopen(str.c_str(), "rb");

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
}

void Maze::init(Program* program)
{
	wall = new Cube(program);
	floor = new Cube(program);
}

Maze::~Maze()
{
}

void Maze::draw(Program* program)
{
	wall->bind(program);
	for (const glm::vec3 pos : walls) {
		glm::mat4 transform;
		transform = glm::scale(transform, size * glm::vec3(0.9999f, 0.9999f, 0.9999f));
		transform = glm::translate(transform, size * glm::vec3(pos));
		program->setMat4(transform, "transform");
		wall->draw();
	}

	floor->bind(program);
	for (int i = 0; i < width * height; i++)
	{
		glm::mat4 transform;
		transform = glm::scale(transform, size * glm::vec3(0.9999f, 0.9999f, 0.9999f));
		transform = glm::translate(transform, size * glm::vec3(x(i), -1.0f, y(i)));
		program->setMat4(transform, "transform");
		floor->draw();
	}

}

Tile* Maze::copyBoard()
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

	Direction dir_x = Direction::UNKNOWN, dir_z = Direction::UNKNOWN;

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

	if (dir_x == Direction::UNKNOWN && dir_z == Direction::UNKNOWN) {
		return false;
	}

	bool collide = false;

	float x1 = size, z1 = size;
	float x2 = size, z2 = size;

	if (dir_x == Direction::EAST && pos_x - cur_x > 0 && tiles[i(cur_x + 1, cur_z)]) {
		x1 = ((cur_x + 1) * size - PLAYER_OFFSET) - current.x;
		if (x1 * x1 < MIN_RESPONSE && direction.x * direction.x < MIN_COLLISION) {
			z1 = direction.z * RESPONSE;
		} else {
			z1 = (x1 * (position.z - current.z)) / max(position.x - current.x, MIN_DST);
		}

		collide = true;
	} else if (dir_x == Direction::WEST && pos_x - cur_x < 0 && tiles[i(cur_x - 1, cur_z)]) {
		x1 = ((cur_x)* size + PLAYER_OFFSET) - current.x;
		if (x1 * x1 < MIN_RESPONSE && direction.x * direction.x < MIN_COLLISION) {
			z1 = direction.z * RESPONSE;
		} else {
			z1 = (x1 * (position.z - current.z)) / max(position.x - current.x, MIN_DST);
		}

		collide = true;
	}

	if (dir_z == Direction::NORTH && pos_z - cur_z > 0 && tiles[i(cur_x, cur_z + 1)]) {
		z2 = ((cur_z + 1) * size - PLAYER_OFFSET) - current.z;
		if (z2 * z2 < MIN_RESPONSE && direction.z * direction.z < MIN_COLLISION * 0.75) {
			x2 = direction.x * RESPONSE;
		} else {
			x2 = (z2 * (position.x - current.x)) / max(position.z - current.z, MIN_DST);
		}

		collide = true;
	} else if (dir_z == Direction::SOUTH && pos_z - cur_z < 0 && tiles[i(cur_x, cur_z - 1)]) {
		z2 = ((cur_z)* size + PLAYER_OFFSET) - current.z;
		if (z2 * z2 < MIN_RESPONSE && direction.z * direction.z < MIN_COLLISION) {
			x2 = direction.x * RESPONSE;
		} else {
			x2 = (z2 * (position.x - current.x)) / max(position.z - current.z, MIN_DST);
		}

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
