#version 330 core

in vec2 tex_coord;

uniform sampler2D texture2D;
out vec4 vcolor;

void main()
{
	vcolor = texture(texture2D, tex_coord);
}