#pragma once

#include <GL/glew.h>
#include <map>
#include <gtc/type_ptr.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat3x3.hpp>
#include <mat4x4.hpp>

class Shader
{
	const char* path = "resources/";
	GLuint shader;
	GLuint program;
public:
	Shader(const char* fname, GLenum type, GLuint program);
	~Shader();
	void setFloat(const GLfloat& value, const char* uniform);
	void setVec3(const glm::vec3& value, const char* uniform);
	void setVec4(const glm::vec4& value, const char* uniform);
	void setMat3(const glm::mat3& value, const char* uniform);
	void setMat4(const glm::mat4& value, const char* uniform);
};