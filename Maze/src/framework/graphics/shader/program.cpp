#include "program.h"
#include "../../../util/log.h"

#include <iostream>

Program::Program()
{
	program = glCreateProgram();
}


Program::~Program() {
	glDeleteProgram(program);
	for (const Shader* shader : shaders) {
		delete shader;
	}
}

void Program::link()
{
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status) {
		GLchar info[512];
		glGetProgramInfoLog(program, 512, nullptr, info);
		Log::error(info);
	}
}

void Program::use()
{
	glUseProgram(program);
}

Program* Program::addShader(const char* fname, GLenum type)
{
	try {
		shaders.push_back(new Shader(fname, type, program));
	} catch (std::runtime_error e) {
		throw;
	}

	return this;
}

GLint Program::getAttr(const char* name)
{
	return glGetAttribLocation(program, name);
}


void Program::setInt(const GLint& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1) {
		glUniform1i(location, value);
	}
}

void Program::setFloat(const GLfloat& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1) {
		glUniform1f(location, value);
	}
}

void Program::setVec3(const glm::vec3& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1) {
		glUniform3f(location, value.x, value.y, value.z);
	}
}
void Program::setVec4(const glm::vec4& value, const char* uniform)
{

	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1) {
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
}
void Program::setMat3(const glm::mat3& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1) {
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}
void Program::setMat4(const glm::mat4& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}
