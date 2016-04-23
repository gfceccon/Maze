#pragma once

#include <GL/glew.h>

class Shader
{
	private:
		const char* path = "resources/";
	public:
		Shader(const char* fname, GLenum type, GLuint program);
};
