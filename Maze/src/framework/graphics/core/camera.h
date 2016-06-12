#pragma once

#include <GL/glew.h>
#include "../shader/program.h"
#include "../shader/shader.h"
#include "../../../util/glm/vec3.hpp"
#include "../../../util/glm/matrix.hpp"
#include "../../../util/glm/gtc/matrix_transform.hpp"
#include "../../../util/glm/gtc/type_ptr.hpp"
#include "../../../maze/player.h"

#define MIN_FOV 15.0f
#define MAX_FOV 120.0f
#define MIN_NEAR 0.1f
#define MAX_FAR 100.0f
#define LIMIT_PITCH 89.0f

#define VIEW_POSITION_NAME "ViewPosition"
#define VIEW_MATRIX_NAME "view"
#define PROJECTION_MATRIX_NAME "projection"


class Camera
{
	friend class Player;

	int width, height;
	float aspect;
	glm::mat4 projection;
	glm::mat4 view;
	float fov = 45.0f;
	float near = 0.1f, far = 100.0f;
	float pitch = 0.0f, yaw = 0.0f, roll = 0.0f;
	const glm::vec3 globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 front, up, right;
	glm::vec3 position;

public:
	Camera(int width, int height);
	~Camera();

	void setProjectionPersp(float fov, float near, float far);
	void setProjectionOrtho(float x, float y, float width, float height);
	void bind(Program* program);
	void update(Player* player);

	void zoom(float amount);
	void addEuler(float pitch, float yaw, float roll);
};

