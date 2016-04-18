#version 150

out vec4 vcolor;
uniform vec3 color;

void main()
{
	vcolor = vec4(color, 1.0);
}