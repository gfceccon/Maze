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

Maze::Maze(int width, int height, float size) :
size(size), cube(nullptr), lights(new MultipleLight(MAX_LIGHTS)), pointLights(new PointLight[MAX_LIGHTS])
{
	height = height + ((height + 1) % 2);
	width = width + ((width + 1) % 2);
	this->width = width;
	this->height = height;

	ProceduralMaze procedural_maze = ProceduralMaze(width, height);
	procedural_maze.generate();

	std::map<std::pair<int, int>, Tile> grid = procedural_maze.getGrid();
	tiles = new Tile*[width];
	lightPositions = new Tile*[width];
	killZones = new Tile*[width];
	for (int x = 0; x < width; x++) {
		tiles[x] = new Tile[height];
		lightPositions[x] = new Tile[height];
		killZones[x] = new Tile[height];
		for (int y = 0; y < height; y++)
		{
			std::pair<int, int> pos = std::make_pair(x, y);

			tiles[x][y] = grid[pos];
			lightPositions[x][y] = Tile::EMPTY;
			killZones[x][y] = Tile::EMPTY;

			// If it's a wall or empty, jump
			if (tiles[x][y] == Tile::EMPTY || tiles[x][y] == Tile::WALL)
				continue;
			// Otherwise, process tile
			else if (tiles[x][y] == Tile::KILL_ZONE)
				killZones[x][y] = Tile::KILL_ZONE;
			else if (tiles[x][y] == Tile::LIGTH) {
				placeLight(x, y);
			}
			else if (tiles[x][y] == Tile::ENTRY) {
				entry = glm::vec3(x, 0.0f, y);
			}
			else if (tiles[x][y] == Tile::EXIT) {
				exit = glm::vec3(x, 0.0f, y);
			}
			// Clear tile
			tiles[x][y] = Tile::EMPTY;
		}
	}

	procedural_maze.print();
}

Maze::Maze(const char* bmp, float size) :
size(size), cube(nullptr), lights(new MultipleLight(MAX_LIGHTS)), pointLights(new PointLight[MAX_LIGHTS])
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
	lightPositions = new Tile*[width];
	killZones = new Tile*[width];
	for (int x = 0; x < width; x++) {
		tiles[x] = new Tile[height];
		lightPositions[x] = new Tile[height];
		killZones[x] = new Tile[height];
		for (int y = 0; y < height; y++)
		{
			bool r = image[y * width + x].red && 0xFF;
			bool g = image[y * width + x].green && 0xFF;
			bool b = image[y * width + x].blue && 0xFF;

			// Default is empty
			tiles[x][y] = Tile::EMPTY;

			// BLACK - WALL
			if (!r && !g && !b) {
				tiles[x][y] = Tile::WALL;
			}
			// BLUE - ENTRY
			else if (!r && !g && b) {
				entry = glm::vec3(x, 0.0f, y);
			}
			// GREEN - EXIT
			else if (!r && g && !b) {
				exit = glm::vec3(x, 0.0f, y);
			}
			// RED - KILL ZONE
			else if (r && !g && !b) {
				killZones[x][y] = Tile::KILL_ZONE;
			}
			// YELLOW - LIGHT
			else if (r && g && !b) {
				placeLight(x, y);
			}
		}
	}
	fclose(f);
}

void Maze::placeLight(int x, int y)
{
	int deltaX = (tiles[x + 1][y - 1] == Tile::WALL) ? 1 : 0
		+ (tiles[x + 1][y] == Tile::WALL) ? 1 : 0
		+ (tiles[x + 1][y + 1] == Tile::WALL) ? 1 : 0
		- (tiles[x - 1][y - 1] == Tile::WALL) ? 1 : 0
		- (tiles[x - 1][y] == Tile::WALL) ? 1 : 0
		- (tiles[x - 1][y + 1] == Tile::WALL) ? 1 : 0;
	int deltaY = (tiles[x - 1][y + 1] == Tile::WALL) ? 1 : 0
		+ (tiles[x][y + 1] == Tile::WALL) ? 1 : 0
		+ (tiles[x + 1][y + 1] == Tile::WALL) ? 1 : 0
		- (tiles[x - 1][y + 1] == Tile::WALL) ? 1 : 0
		- (tiles[x][y + 1] == Tile::WALL) ? 1 : 0
		- (tiles[x + 1][y + 1] == Tile::WALL) ? 1 : 0;

	// Try placing best wall
	if (deltaY > 0 && tiles[x][y + 1] == Tile::WALL)
		lightPositions[x][y] = Tile::NORTH_LIGHT;
	else if (deltaY < 0 && tiles[x][y - 1] == Tile::WALL)
		lightPositions[x][y] = Tile::SOUTH_LIGHT;
	else if (deltaX > 0 && tiles[x + 1][y] == Tile::WALL)
		lightPositions[x][y] = Tile::RIGHT_LIGHT;
	else if (deltaX < 0 && tiles[x - 1][y] == Tile::WALL)
		lightPositions[x][y] = Tile::LEFT_LIGHT;

	// Can't place light, try others
	else if (tiles[x][y - 1] == Tile::WALL)
		lightPositions[x][y] = Tile::SOUTH_LIGHT;
	else if (tiles[x + 1][y] == Tile::WALL)
		lightPositions[x][y] = Tile::RIGHT_LIGHT;
	else if (tiles[x][y + 1] == Tile::WALL)
		lightPositions[x][y] = Tile::NORTH_LIGHT;
	else if (tiles[x - 1][y] == Tile::WALL)
		lightPositions[x][y] = Tile::LEFT_LIGHT;

	// Place kill zone if there is any near
	if (tiles[x - 1][y + 1] == Tile::KILL_ZONE || tiles[x][y + 1] == Tile::KILL_ZONE || tiles[x + 1][y + 1] == Tile::KILL_ZONE ||
		tiles[x - 1][y] == Tile::KILL_ZONE || tiles[x][y] == Tile::KILL_ZONE || tiles[x + 1][y] == Tile::KILL_ZONE ||
		tiles[x - 1][y - 1] == Tile::KILL_ZONE || tiles[x][y - 1] == Tile::KILL_ZONE || tiles[x + 1][y - 1] == Tile::KILL_ZONE)
		killZones[x][y] = Tile::KILL_ZONE;
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

	for (int i = 0; i < width; i++)
		delete lightPositions[i];
	delete lightPositions;

	for (int i = 0; i < width; i++)
		delete killZones[i];
	delete killZones;

	delete cube;
	delete floor;
	delete wall;
	delete lights;
	delete pointLights;
}
// Draw maze
void Maze::draw(Program* program)
{
	// Bind object
	cube->bind(program);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			glm::mat4 transform;
			glm::vec3 position;
			// Scale size
			transform = glm::scale(transform, size * glm::vec3(0.9999f, 0.9999f, 0.9999f));
			// Bind materials and position (floor or wall)
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
			// Translate to position and bind
			transform = glm::translate(transform, size * glm::vec3(position));
			program->setMat4(transform, "transform");

			// Bind point lights and directional light
			bindLights(x, y);
			lights->bind(program);
			

			// Draw cube (floor or wall)
			cube->draw();
		}
	}
}

glm::vec3 Maze::getEntryPosition()
{
	return entry * size + glm::vec3(size / 2, PLAYER_HEIGHT, size / 2);
}

// Set light from multiple lights on index
void Maze::setLightPosition(int& index, int x, int y)
{
	// Exit if out of bounds
	if (x < 0 || x >= width)
		return;
	if (y < 0 || y >= height)
		return;

	// Select light position
	switch (lightPositions[x][y])
	{
	case Tile::NORTH_LIGHT:
		pointLights[index].setPosition((x + 0.5f) * size, LIGHT_HEIGHT, (y + 1) * size - LIGHT_OFFSET);
		break;
	case Tile::SOUTH_LIGHT:
		pointLights[index].setPosition((x + 0.5f) * size, LIGHT_HEIGHT, y * size + LIGHT_OFFSET);
		break;
	case Tile::RIGHT_LIGHT:
		pointLights[index].setPosition((x + 1) * size - LIGHT_OFFSET, LIGHT_HEIGHT, (y + 0.5f) * size);
		break;
	case Tile::LEFT_LIGHT:
		pointLights[index].setPosition(x * size + LIGHT_OFFSET, LIGHT_HEIGHT, (y + 0.5f) * size);
		break;
	default:
		break;
	}
	lights->addLight(&pointLights[index]);
	index++;
}

// Bind multiple lights
void Maze::bindLights(int x, int y)
{
	lights->clear();
	int index = 0;
	int X = x - 1, Y = y - 1;
	for (int X = x - 1; X <= x + 1; X++)
		for (int Y = y - 1; Y <= y + 1; Y++)
			if (lightPositions[X][Y] != Tile::EMPTY)
				setLightPosition(index, X, Y);
}

inline float max(float x, float y)
{
	return x > y ? x : y;
}

// Collision detection and response
bool Maze::checkCollision(glm::vec3 current, glm::vec3& position)
{
	// Get current position
	int cur_x = static_cast<int>(floorf(current.x / size));
	int cur_z = static_cast<int>(floorf(current.z / size));

	int pos_x = cur_x, pos_z = cur_z;

	// Get direction
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
	
	// If there is no change in position, quit
	if (dir_x == Direction::UNKNOWN && dir_z == Direction::UNKNOWN) {
		return false;
	}

	// Collision detection
	bool collide = false;

	float x1 = size, z1 = size;
	float x2 = size, z2 = size;

	// Calculate new X and Z based on collision
	// Use similar triangles to calculate collision response
	
	// EAST COLLISION DETECTION
	if (dir_x == Direction::EAST && pos_x - cur_x > 0 && tiles[cur_x + 1][cur_z] == Tile::WALL) {
		x1 = ((cur_x + 1) * size - PLAYER_OFFSET) - current.x;
		if (x1 * x1 < MIN_RESPONSE && direction.x * direction.x < MIN_COLLISION) {
			z1 = direction.z * RESPONSE;
		}
		else {
			z1 = (x1 * (position.z - current.z)) / max(position.x - current.x, MIN_DST);
		}

		collide = true;
	}
	// WEST COLLISION DETECTION
	else if (dir_x == Direction::WEST && pos_x - cur_x < 0 && tiles[cur_x - 1][cur_z] == Tile::WALL) {
		x1 = ((cur_x)* size + PLAYER_OFFSET) - current.x;
		if (x1 * x1 < MIN_RESPONSE && direction.x * direction.x < MIN_COLLISION) {
			z1 = direction.z * RESPONSE;
		}
		else {
			z1 = (x1 * (position.z - current.z)) / max(position.x - current.x, MIN_DST);
		}

		collide = true;
	}

	// NORTH COLLISION DETECTION
	if (dir_z == Direction::NORTH && pos_z - cur_z > 0 && tiles[cur_x][cur_z + 1] == Tile::WALL) {
		z2 = ((cur_z + 1) * size - PLAYER_OFFSET) - current.z;
		if (z2 * z2 < MIN_RESPONSE && direction.z * direction.z < MIN_COLLISION * 0.75) {
			x2 = direction.x * RESPONSE;
		}
		else {
			x2 = (z2 * (position.x - current.x)) / max(position.z - current.z, MIN_DST);
		}

		collide = true;
	}
	// SOUTH COLLISION DETECTION
	else if (dir_z == Direction::SOUTH && pos_z - cur_z < 0 && tiles[cur_x][cur_z - 1] == Tile::WALL) {
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

	// Choose best collision between W-E, N-S
	if (x1 * x1 + z1 * z1 < x2 * x2 + z2 * z2) {
		position = current + glm::vec3(x1, 0, z1);
	}
	else {
		position = current + glm::vec3(x2, 0, z2);
	}

	return collide;
}
