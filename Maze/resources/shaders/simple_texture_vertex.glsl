#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

out vec2 tex_coord;

void main()
{
    gl_Position = vec4(position, 1.0f); 
    tex_coord = vec2(uv.x, 1.0 - uv.y);
} 
