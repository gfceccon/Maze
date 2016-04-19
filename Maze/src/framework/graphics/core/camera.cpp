#include "camera.h"

#include <cfloat>
#include <util/log.h>

Camera::Camera(int w, int h) : width(w), height(h)
{
	aspect = (float)w / (float)h;
	SetProjectionPersp(fov, near, far);
	//SetProjectionOrtho();
}

Camera::~Camera()
{
}

void Camera::SetProjectionOrtho()
{
	projection = glm::ortho<float>(0.0f, width, 0.0f, height);
}

void Camera::SetProjectionPersp(float fov, float near, float far)
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

void Camera::Bind(Program* program)
{
	program->SetMat4(projection, projectionName);
	program->SetMat4(view, viewName);
}


void Camera::Translate(float x, float y, float z)
{
	glm::vec3 translation(x, y, z);
	view = glm::translate(view, translation);
}

void Camera::Rotate(Axis axis, float degrees)
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

void Camera::Scale(float x, float y, float z)
{
	glm::vec3 scale(x, y, z);
	view = glm::scale(view, scale);
}


void Camera::Move(Axis direction, float amount)
{
	glm::vec3 right = this->right;
	right.y = 0.0f;
	glm::vec3 front = this->front;
	front.y = 0.0f;
	switch (direction)
	{
	case X:
		position = position + amount * right;
		break;
	case Y:
		position = position + amount * globalUp;
		break;
	case Z:
		position = position + amount * front;
	default:
		break;
	}
	Update();
}

void Camera::Move(float x, float y, float z)
{
	glm::vec3 right = this->right;
	right.y = 0.0f;
	glm::vec3 front = this->front;
	front.y = 0.0f;

	position = position + x * right;
	position = position + y * globalUp;
	position = position + z * front;
	Update();
}

void Camera::Zoom(float amount)
{
	float value = fov * amount;
	if (fov > MAX_FOV)
		fov = MAX_FOV;
	if (fov < MIN_FOV)
		fov = MIN_FOV;
	else
		fov = value;
	SetProjectionPersp(fov, near, far);
}

void Camera::AddEuler(float pitch, float yaw, float roll)
{
	if (this->pitch + pitch > LIMIT_PITCH)
		this->pitch = LIMIT_PITCH;
	if (this->pitch + pitch < -LIMIT_PITCH)
		this->pitch = -LIMIT_PITCH;
	else
		this->pitch += pitch;

	Log::Print(this->pitch);

	this->yaw += yaw;
	this->roll += roll;

	glm::vec3 front;
	front.x = cosf(glm::radians(this->yaw)) * cosf(glm::radians(this->pitch));
	front.y = sinf(glm::radians(this->pitch));
	front.z = sinf(glm::radians(this->yaw)) * cosf(glm::radians(this->pitch));

	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, globalUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
	Update();
}

void Camera::Update()
{
	view = glm::lookAt(position, position + front, up);
}