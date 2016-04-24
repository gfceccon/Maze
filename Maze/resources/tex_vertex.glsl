#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 color;

out vec2 tex_coord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

void main()
{
	gl_Position = projection * view * transform * vec4(position, 1.0);
    tex_coord = vec2(texCoord.x, 1.0 - texCoord.y);
}
