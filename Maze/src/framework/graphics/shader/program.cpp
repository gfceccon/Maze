#include "program.h"

#include <util/log.h>

Program::Program()
{
	program = glCreateProgram();
}


Program::~Program()
{
	for (const Shader* shader : shaders)
		delete shader;
	glDeleteProgram(program);
}

void Program::Link()
{
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status)
	{
		GLchar info[512];
		glGetProgramInfoLog(program, 512, nullptr, info);
		Log::Error(info);
	}
}

void Program::Use()
{
	glUseProgram(program);
}

Program* Program::AddShader(const char* fname, GLenum type)
{
	shaders.push_back(new Shader(fname, type, program));
	return this;
}


void Program::SetFloat(const GLfloat& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1)
		glUniform1f(location, value);
}

void Program::SetVec3(const glm::vec3& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1)
		glUniform3f(location, value.x, value.y, value.z);
}
void Program::SetVec4(const glm::vec4& value, const char* uniform)
{

	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1)
		glUniform4f(location, value.x, value.y, value.z, value.w);
}
void Program::SetMat3(const glm::mat3& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1)
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
void Program::SetMat4(const glm::mat4& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}