#pragma once


#include <queue>
#include <iostream>

#include "maze/player.h"
#include "framework/game/window.h"
#include "framework/game/event.h"
#include "framework/game/scene.h"
#include "framework/graphics/core/camera.h"
#include "framework/graphics/shader/program.h"
#include "framework/graphics/shader/shader.h"

#include "framework/graphics/model/material.h"
#include "framework/graphics/core/point_light.h"
#include "framework/graphics/core/multiple_light.h"
#include "framework/graphics/core/directional_light.h"
#include "framework/graphics/model/primitive/advanced_cube.h"

#include "util/log.h"
#include "util/color.h"
#include "util/glm/vec3.hpp"
#include "util/glm/mat4x4.hpp"
#include "util/glm/gtc/matrix_transform.hpp"

#define MAX_TEST_LIGHTS 9

class Test : public Scene
{
private:
	Program* program;
	
	Player* player;
	Camera* camera;

	AdvancedCube* cube;
	Material* material;

	PointLight pointLights[MAX_TEST_LIGHTS];
	MultipleLight* lights;
	DirectionalLight* directional;
	float size;
	float angle;
	float attConst, attLinear, attQuad;
	

	float move_sensibility = 10.0f, zoom_sensibility = .98f, rotation_sensibility = 20.0f;
public:
	Test();
	~Test();

	void update(float delta) override;
	void draw(float delta) override;
};

