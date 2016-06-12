#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <queue>
#include "../util/glm/vec3.hpp"
#include "../util/glm/mat4x4.hpp"
#include "../util/glm/gtc/matrix_transform.hpp"

#include "maze.h"
#include "player.h"
#include "../util/color.h"
#include "../framework/game/event.h"
#include "../framework/game/scene.h"
#include "../framework/graphics/core/camera.h"
#include "../framework/graphics/shader/program.h"
#include "../framework/graphics/shader/shader.h"
#include "../framework/graphics/effects/chrom_aberr.h"

class Game : public Scene
{
	Player* player;
	Camera* camera;
	Program* program;
	Maze* maze;

    glm::vec3 gravity = glm::vec3(0.0f, -9.8f, 0.0f);
	float move_sensibility = 0.083f, zoom_sensibility = .98f, rotation_sensibility = 20.0f;
public:
	Game(int width, int height);
	~Game();

	void update(float delta) override;
	void draw(float delta) override;
};
