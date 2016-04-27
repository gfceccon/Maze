#version 330 core

in vec2 tex_coord;
out vec4 color;

uniform sampler2D texture2D;

void main()
{ 
    color = vec4(vec3(1.0 - texture(texture2D, tex_coord)), 1.0);
}