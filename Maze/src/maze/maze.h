#pragma once

#include <cstring>
#include <vector>
#include "../util/glm/vec2.hpp"
#include "../util/glm/gtc/matrix_transform.hpp"
#include "../framework/graphics/shader/program.h"
#include "../framework/graphics/model/primitive/advanced_cube.h"
#include "../framework/graphics/core/directional_light.h"
#include "../framework/graphics/core/multiple_light.h"
#include "../framework/graphics/core/point_light.h"

#define PLAYER_OFFSET 0.15f
#define PLAYER_HEIGHT 0.5f

#define RESPONSE 1.0f
#define MIN_DST 1.0f
#define MIN_RESPONSE 0.01f
#define MIN_COLLISION 7e-5

#define LIGHT_HEIGHT 0.5f
#define LIGHT_OFFSET 0.1f
#define MAX_LIGHTS 4

enum Tile
{
	EMPTY,
	WALL,
	ENTRY,
	EXIT,
	LIGTH,

	NORTH_LIGHT,
	RIGHT_LIGHT,
	SOUTH_LIGHT,
	LEFT_LIGHT,

	KILL_ZONE,
	VISITED,
	UNVISITED,
	LIGHT
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
private:
	int width, height;
	Tile** tiles, **lightPositions, **killZones;
	glm::vec3 entry, exit;

	AdvancedCube* cube;
	Material *wall, *floor;
	DirectionalLight* directionalLight;
	PointLight* pointLights;
	MultipleLight* lights;

	float size;
	const char* path = "resources/";


	size_t i(size_t x, size_t y) { return y * width + x; }
	size_t x(size_t i) { return i % width; }
	size_t y(size_t i) { return i / width; }
	void bindLights(int x, int y);
	void setLightPosition(int& index, int x, int Y);
	void placeLight(int x, int y);
public:
	Maze(int width, int height, float size = 1.0f);
	Maze(const char* bmp, float size = 1.0f);
	~Maze();
	void init(Program* program);
	void draw(Program* program);
	glm::vec3 getEntryPosition();
	bool checkCollision(glm::vec3 current, glm::vec3& position);
};

