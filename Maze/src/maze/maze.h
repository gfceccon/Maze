#pragma once

#include "../util/glm/gtc/matrix_transform.hpp"
#include "../util/glm/vec2.hpp"
#include <cstring>
#include <vector>
#include "../framework/graphics/shader/program.h"
#include "../framework/graphics/model/primitive/cube.h"

#define PLAYER_OFFSET 0.15f
#define RESPONSE 1.0f
#define PLAYER_HEIGHT 0.5f
#define MIN_DST 1.0f
#define MIN_RESPONSE 0.01f
#define MIN_COLLISION 7e-5

enum Tile
{
	EMPTY,
	WALL,
	ENTRY,
	EXIT,
	VISITED,
	UNVISITED
};

enum Direction
{
	UNKNOWN,
	NORTH,
	SOUTH,
	WEST,
	EAST
};

class Maze
{
	int width, height;
	Tile* tiles;
	Cube* wall = nullptr;
	Cube* floor = nullptr;
	float size;
	glm::vec3 entry, exit;
	std::vector<glm::vec3> walls;
	const char* path = "resources/";


	size_t i(size_t x, size_t y) { return y * width + x; }
	size_t x(size_t i) { return i % width; }
	size_t y(size_t i) { return i / width; }
public:
	Maze(int width, int height, float size = 1.0f);
	Maze(const char* bmp, float size = 1.0f);
	~Maze();
	void init(Program* program);
	void draw(Program* program);
	Tile* copyBoard();
	glm::vec3 getEntryPosition();
	bool checkCollision(glm::vec3 current, glm::vec3& position);
};

