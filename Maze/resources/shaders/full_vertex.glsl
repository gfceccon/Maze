#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec3 FragPosition;
out vec2 TexCoord;
out mat3 TBN;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	vec4 Position = view * model * vec4(position, 1.0);
	
	FragPosition = vec3(model * vec4(position, 1.0));
	
    mat3 normalMatrix = transpose(inverse(mat3(model)));
	
    TexCoord = vec2(uv.x, 1.0 - uv.y);

    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);    
    
    TBN = transpose(mat3(T, B, N)); 
	
	gl_Position = projection * Position;
}
