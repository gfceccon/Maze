#include "camera.h"

#include <cfloat>
#include "../../../util/log.h"

Camera::Camera(int w, int h) : width(w), height(h)
{
	aspect = (float)w / (float)h;
	setProjectionPersp(fov, near, far);

	up = glm::vec3();
	front = glm::vec3();
	right = glm::vec3();
}

Camera::~Camera()
{
}

void Camera::setProjectionOrtho(float x, float y, float width, float height)
{
	projection = glm::ortho<float>(x, x + width, y, y + height);
}

void Camera::setProjectionPersp(float fov, float near, float far)
{
	if (fov < FLT_EPSILON || fov > MAX_FOV) {
		return;
	}

	if (near < FLT_EPSILON || far < FLT_EPSILON) {
		return;
	}

	if (near < MIN_NEAR || far > MAX_FAR) {
		return;
	}

	this->fov = fov;
	this->near = near;
	this->far = far;
	projection = glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::bind(Program* program)
{
	program->setMat4(projection, projectionName);
	program->setMat4(view, viewName);
}

void Camera::zoom(float amount)
{
	float value = fov * amount;
	if (fov > MAX_FOV) {
		fov = MAX_FOV;
	}

	if (fov < MIN_FOV) {
		fov = MIN_FOV;
	} else {
		fov = value;
	}

	setProjectionPersp(fov, near, far);
}

void Camera::addEuler(float pitch, float yaw, float roll)
{
	if (this->pitch + pitch > LIMIT_PITCH) {
		this->pitch = LIMIT_PITCH;
	}

	if (this->pitch + pitch < -LIMIT_PITCH) {
		this->pitch = -LIMIT_PITCH;
	} else {
		this->pitch += pitch;
	}

	this->yaw += yaw;
	this->roll += roll;

	glm::vec3 front;
	front.x = cosf(glm::radians(this->yaw)) * cosf(glm::radians(this->pitch));
	front.y = sinf(glm::radians(this->pitch));
	front.z = sinf(glm::radians(this->yaw)) * cosf(glm::radians(this->pitch));

	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, globalUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

void Camera::update(Player* player)
{
	if (player) {
		player->front = this->front;
		player->right = this->right;
		player->up = this->up;
		this->position = player->position;
	}

	view = glm::lookAt(position, position + front, up);
}
