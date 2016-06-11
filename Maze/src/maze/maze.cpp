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

Maze::Maze(int width, int height, float size) : size(size), cube(nullptr)
{
	height = height + ((height + 1) % 2);
	width = width + ((width + 1) % 2);
	this->width = width;
	this->height = height;

	ProceduralMaze procedural_maze = ProceduralMaze(width, height);
	procedural_maze.generate();

	std::map<std::tuple<int, int>, Tile> grid = procedural_maze.getGrid();
	tiles = new Tile*[width];
	for (int x = 0; x < width; x++) {
		tiles[x] = new Tile[height];
		for (int y = 0; y < width; y++)
		{
			std::tuple<int, int> pos = std::make_tuple(x, y);
			tiles[x][y] = grid[pos];
			if (tiles[x][y] == Tile::ENTRY) {
				entry = glm::vec3(x, 0.0f, y);
			}
			else if (tiles[x][y] == Tile::EXIT) {
				exit = glm::vec3(x, 0.0f, y);
			}
		}
	}

	procedural_maze.print();
}

Maze::Maze(const char* bmp, float size) : size(size), cube(nullptr)
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
	tiles = new Tile*[width];
	for (int x = 0; x < width; x++) {
		tiles[x] = new Tile[height];
		for (int y = 0; y < width; y++)
		{
			bool r = image[y * width + x].red && 0xFF;
			bool g = image[y * width + x].green && 0xFF;
			bool b = image[y * width + x].blue && 0xFF;

			if (!(r || g || b)) {
				tiles[x][y] = Tile::WALL;
			}
			else if (r && g && b) {
				tiles[x][y] = Tile::EMPTY;
			}
			else if (!r && !g && b) {
				tiles[x][y] = Tile::ENTRY;
				entry = glm::vec3(x, 0.0f, y);
			}
			else if (r && !g && !b) {
				tiles[x][y] = Tile::EXIT;
				exit = glm::vec3(x, 0.0f, y);
			}
		}
	}
	fclose(f);
}

void Maze::init(Program* program)
{
	std::string resource;
	cube = new AdvancedCube(program);
	floor = new Material();
	wall = new Material();

	resource = path;
	resource += "wall.png";
	wall->initTexture(program, resource.c_str(), Material::TextureType::Diffuse);

	resource = path;
	resource += "floor.png";
	floor->initTexture(program, resource.c_str(), Material::TextureType::Diffuse);
}

Maze::~Maze()
{
	for (int i = 0; i < width; i++)
		delete tiles[i];
	delete tiles;
	delete cube;
	delete floor;
	delete wall;
}

void Maze::draw(Program* program)
{
	cube->bind(program);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			glm::mat4 transform;
			glm::vec3 position;
			transform = glm::scale(transform, size * glm::vec3(0.9999f, 0.9999f, 0.9999f));
			switch (tiles[x][y])
			{

			case Tile::WALL:
				wall->bind(program);
				position = glm::vec3(x, 0.0f, y);
				break;
			case Tile::EMPTY:
				floor->bind(program);
				position = glm::vec3(x, -1.0f, y);
				break;
			}
			transform = glm::translate(transform, size * glm::vec3(position));
			program->setMat4(transform, "transform");
			cube->draw();
		}
	}
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
		}
		else {
			z1 = (x1 * (position.z - current.z)) / max(position.x - current.x, MIN_DST);
		}

		collide = true;
	}
	else if (dir_x == Direction::WEST && pos_x - cur_x < 0 && tiles[i(cur_x - 1, cur_z)]) {
		x1 = ((cur_x)* size + PLAYER_OFFSET) - current.x;
		if (x1 * x1 < MIN_RESPONSE && direction.x * direction.x < MIN_COLLISION) {
			z1 = direction.z * RESPONSE;
		}
		else {
			z1 = (x1 * (position.z - current.z)) / max(position.x - current.x, MIN_DST);
		}

		collide = true;
	}

	if (dir_z == Direction::NORTH && pos_z - cur_z > 0 && tiles[i(cur_x, cur_z + 1)]) {
		z2 = ((cur_z + 1) * size - PLAYER_OFFSET) - current.z;
		if (z2 * z2 < MIN_RESPONSE && direction.z * direction.z < MIN_COLLISION * 0.75) {
			x2 = direction.x * RESPONSE;
		}
		else {
			x2 = (z2 * (position.x - current.x)) / max(position.z - current.z, MIN_DST);
		}

		collide = true;
	}
	else if (dir_z == Direction::SOUTH && pos_z - cur_z < 0 && tiles[i(cur_x, cur_z - 1)]) {
		z2 = ((cur_z)* size + PLAYER_OFFSET) - current.z;
		if (z2 * z2 < MIN_RESPONSE && direction.z * direction.z < MIN_COLLISION) {
			x2 = direction.x * RESPONSE;
		}
		else {
			x2 = (z2 * (position.x - current.x)) / max(position.z - current.z, MIN_DST);
		}

		collide = true;
	}

	if (!collide) {
		return collide;
	}

	if (x1 * x1 + z1 * z1 < x2 * x2 + z2 * z2) {
		position = current + glm::vec3(x1, 0, z1);
	}
	else {
		position = current + glm::vec3(x2, 0, z2);
	}

	return collide;
}
