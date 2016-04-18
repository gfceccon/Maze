#include "shader.h"

#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <util/log.h>

Shader::Shader(const char* fname, GLenum type, GLuint program) : program(program)
{
	std::string str(path);
	str += fname;
	std::ifstream file(str.c_str(), std::ios::in | std::ios::binary);

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string src = buffer.str();
	std::replace(src.begin(), src.end(), '\r', '\n');

	const char* source = src.c_str();

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		GLchar info[512];
		glGetShaderInfoLog(shader, 512, nullptr, info);
		Log::error(info);
	}
	else
		glAttachShader(program, shader);
}

Shader::~Shader()
{
	glDeleteShader(shader);
}

void Shader::setFloat(const GLfloat& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1)
		glUniform1f(location, value);
}

void Shader::setVec3(const glm::vec3& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1)
		glUniform3f(location, value.x, value.y, value.z);
}
void Shader::setVec4(const glm::vec4& value, const char* uniform)
{

	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1)
		glUniform4f(location, value.x, value.y, value.z, value.w);
}
void Shader::setMat3(const glm::mat3& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1)
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setMat4(const glm::mat4& value, const char* uniform)
{
	GLint location = glGetUniformLocation(program, uniform);
	if (location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}