#pragma once

#include <GL/glew.h>
#include <framework/graphics/shader/program.h>
#include <framework/graphics/shader/shader.h>
#include <matrix.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define MIN_FOV 15.0f
#define MAX_FOV 120.0f
#define MIN_NEAR 0.1f
#define MAX_FAR 100.0f
#define LIMIT_PITCH 89.0f

enum Axis
{
	X, Y, Z
};

class Camera
{
	int width, height;
	float aspect;
	glm::mat4 projection;
	glm::mat4 view;
	float fov = 45.0f;
	float near = 0.1f, far = 100.0f;
	const char* viewName = "view", *projectionName = "projection";
	float pitch = 0.0f, yaw = 0.0f, roll = 0.0f;
	const glm::vec3 globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 front, up, right;
	glm::vec3 position;

	void Translate(float x, float y, float z);
	void Rotate(Axis axis, float degrees);
	void Scale(float x, float y, float z);

public:
	Camera(int width, int height);
	~Camera();

	void SetProjectionPersp(float fov, float near, float far);
	void SetProjectionOrtho();
	void Bind(Program* program);
	void Update();

	void Move(Axis direction, float amount);
	void Move(float x, float y, float z);
	void Zoom(float amount);
	void AddEuler(float pitch, float yaw, float roll);
};

