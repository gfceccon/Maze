#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec2 normal;
layout (location = 3) in vec3 color;
layout (location = 4) in vec3 materialIndex;

out vec3 FragPosition;
out vec2 TexCoord;
out vec3 Normal;
out int MaterialIndex;
out vec3 Eye;
out vec4 Position;

uniform vec3 ViewPosition;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	Position = view * model * vec4(position, 1.0);
	
	Eye = -(Position);
	
	FragPosition = vec3(model * vec4(position, 1.0));
	
    Normal = mat3(transpose(inverse(model))) * normal; 
	
    TexCoord = vec2(uv.x, 1.0 - uv.y);
	
	MaterialIndex = (int) material;
	
	
	gl_Position = projection * view * model * vec4(position, 1.0);
}
