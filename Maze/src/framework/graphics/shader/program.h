#pragma once

#include <GL/glew.h>
#include <framework/graphics/shader/shader.h>
#include <vector>
#include <gtc/type_ptr.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat3x3.hpp>
#include <mat4x4.hpp>

class Program
{
	GLuint program;
	std::vector<Shader*> shaders;
public:
	Program();
	~Program();

	Program* AddShader(const char* fname, GLenum type);
	void Link();
	void Use();

	void SetFloat(const GLfloat& value, const char* uniform);
	void SetVec3(const glm::vec3& value, const char* uniform);
	void SetVec4(const glm::vec4& value, const char* uniform);
	void SetMat3(const glm::mat3& value, const char* uniform);
	void SetMat4(const glm::mat4& value, const char* uniform);
};

