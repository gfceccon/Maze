#pragma once

#include <GL/glew.h>

class Color
{
	float h, s, v;
public:
	GLclampf r, g, b, a;
	Color(GLclampf r = 1.0f, GLclampf g = 1.0f, GLclampf b = 1.0f, GLclampf a = 1.0f);
	~Color();
};

