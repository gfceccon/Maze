#pragma once

#include <GL/glew.h>

class Shader
{
	const char* path = "resources/";
	GLuint shader;
	GLuint program;
public:
	Shader(const char* fname, GLenum type, GLuint program);
	~Shader();
};