#include "program.h"
#include "../../../util/log.h"

#include <iostream>

Program::Program()
{
	prog = glCreateProgram();
}


Program::~Program() {
	glDeleteProgram(prog);
	for (const Shader* shader : shaders) {
		delete shader;
	}
}

#define PROGRAM_LINK_ERROR_BUFFER 1024

void Program::link()
{
	glLinkProgram(prog);

	GLint status;
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (!status) {
		GLchar info[PROGRAM_LINK_ERROR_BUFFER];
		glGetProgramInfoLog(prog, PROGRAM_LINK_ERROR_BUFFER, nullptr, info);
		Log::error(info);
	}
}

void Program::use()
{
	glUseProgram(prog);
}

Program* Program::addShader(const char* fname, GLenum type)
{
	try {
		shaders.push_back(new Shader(fname, type, prog));
	} catch (std::runtime_error e) {
		throw;
	}

	return this;
}

GLint Program::getAttr(const char* name)
{
	return glGetAttribLocation(prog, name);
}


void Program::setInt(const GLint& value, const char* uniform)
{
	GLint location = glGetUniformLocation(prog, uniform);
	if (location != -1) {
		glUniform1i(location, value);
		//Log::print("Uniform found:");
		//Log::print(uniform);
	}
}

void Program::setFloat(const GLfloat& value, const char* uniform)
{
	GLint location = glGetUniformLocation(prog, uniform);
	if (location != -1) {
		glUniform1f(location, value);
		//Log::print("Uniform found:");
		//Log::print(uniform);
	}
}

void Program::setVec2(const glm::vec2& value, const char* uniform)
{
	GLint location = glGetUniformLocation(prog, uniform);
	if (location != -1) {
		glUniform2f(location, value.x, value.y);
		//Log::print("Uniform found:");
		//Log::print(uniform);
	}
}
void Program::setVec3(const glm::vec3& value, const char* uniform)
{
	GLint location = glGetUniformLocation(prog, uniform);
	if (location != -1) {
		glUniform3f(location, value.x, value.y, value.z);
		//Log::print("Uniform found:");
		//Log::print(uniform);
	}
}
void Program::setVec4(const glm::vec4& value, const char* uniform)
{

	GLint location = glGetUniformLocation(prog, uniform);
	if (location != -1) {
		glUniform4f(location, value.x, value.y, value.z, value.w);
		//Log::print("Uniform found:");
		//Log::print(uniform);
	}
}
void Program::setMat3(const glm::mat3& value, const char* uniform)
{
	GLint location = glGetUniformLocation(prog, uniform);
	if (location != -1) {
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
		//Log::print("Uniform found:");
		//Log::print(uniform);
	}
}
void Program::setMat4(const glm::mat4& value, const char* uniform)
{
	GLint location = glGetUniformLocation(prog, uniform);
	if (location != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		//Log::print("Uniform found:");
		//Log::print(uniform);
	}
}
