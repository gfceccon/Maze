#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS 9

out vec3 FragPosition;
out vec2 TexCoord;
out DL {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} Directional;
out PL {
    vec3 position;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
} Lights[NR_POINT_LIGHTS];
out vec3 fPos;
out vec3 vPos;
out vec3 vDir;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

uniform vec3 ViewPosition;
uniform DirLight directional;
uniform PointLight lights[NR_POINT_LIGHTS];

void main()
{
	vec4 Position = view * model * vec4(position, 1.0);
	
	FragPosition = vec3(model * vec4(position, 1.0));
	
    mat3 normalMatrix = transpose(inverse(mat3(model)));
	
    TexCoord = vec2(uv.x, 1.0 - uv.y);

    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);    
    
    mat3 TBN = transpose(mat3(T, B, N)); 
	
	fPos = TBN * FragPosition;
	vPos = TBN * ViewPosition;
	vDir = normalize(vPos - fPos);

	Directional.direction = TBN * directional.direction;
	
    Directional.ambient = directional.ambient;
    Directional.diffuse = directional.diffuse;
    Directional.specular = directional.specular;
	
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		Lights[i].position = TBN * lights[i].position;
	
		Lights[i].ambient = lights[i].ambient;
		Lights[i].diffuse = lights[i].diffuse;
		Lights[i].specular = lights[i].specular;
	
		Lights[i].constant = lights[i].constant;
		Lights[i].linear = lights[i].linear;
		Lights[i].quadratic = lights[i].quadratic;
	}
	
	gl_Position = projection * Position;
}
