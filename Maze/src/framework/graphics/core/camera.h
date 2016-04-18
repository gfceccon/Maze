#pragma once

#include <GL/glew.h>
#include <framework/graphics/shader/shader.h>
#include <matrix.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define MAX_FOV 120.0f
#define MIN_NEAR 0.1f
#define MAX_FAR 100.0f

enum Axis
{
	X, Y, Z
};

class Camera
{
	float aspect;
	glm::mat4 projection;
	glm::mat4 view;
	float fov = 45.0f;
	float near = 0.1f, far = 100.0f;
	const char* view_name = "view", *projection_name = "projection";
public:
	Camera(int width, int height);
	~Camera();

	void setProjectionPersp(float fov, float near, float far);
	void setProjectionOrtho();
	void bind(GLuint program, Shader* shader);

	void translate(float x, float y, float z);
	void rotate(Axis axis, float degrees);
	void scale(float x, float y, float z);
};

