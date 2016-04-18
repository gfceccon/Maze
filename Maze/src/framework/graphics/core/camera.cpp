#include "camera.h"

#include <cfloat>

Camera::Camera(int w, int h)
{
	aspect = (float)w / (float)h;
	projection = glm::perspective(glm::radians(fov), aspect, near, far);
}

Camera::~Camera()
{
}

void Camera::setProjectionOrtho()
{
	//projection = glm::ortho<float>(0.0f, width, 0.0f, height);
}

void Camera::setProjectionPersp(float fov, float near, float far)
{
	if (fov < FLT_EPSILON || fov > MAX_FOV)
		return;
	if (near < FLT_EPSILON || far < FLT_EPSILON)
		return;
	if (near < MIN_NEAR || far > MAX_FAR)
		return;
	this->fov = fov;
	this->near = near;
	this->far = far;
	projection = glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::bind(Program* program)
{
	program->setMat4(projection, projection_name);
	program->setMat4(view, view_name);
}


void Camera::translate(float x, float y, float z)
{
	glm::vec3 translation(x, y, z);
	view = glm::translate(view, translation);
}

void Camera::rotate(Axis axis, float degrees)
{
	glm::vec3 rot_axis;
	switch (axis)
	{
	case X:
		rot_axis.x = 1.0f;
		break;
	case Y:
		rot_axis.y = 1.0f;
		break;
	case Z:
		rot_axis.z = 1.0f;
		break;
	default:
		break;
	}
	view = glm::rotate(view, glm::radians(degrees), rot_axis);
}

void Camera::scale(float x, float y, float z)
{
	glm::vec3 scale(x, y, z);
	view = glm::scale(view, scale);
}