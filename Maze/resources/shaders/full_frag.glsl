#version 330 core
struct Material {
    sampler2D diffuse2D;
    sampler2D normal2D;
    sampler2D depth2D;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
    float shininess;
};

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

#define NR_POINT_LIGHTS 4

in vec3 FragPosition;
in vec2 TexCoord;
in vec3 Normal;
in int MaterialIndex;
in vec3 Eye;
in vec3 Position;

out vec4 color;

uniform vec3 ViewPosition;
uniform DirLight directional;
uniform PointLight lights[NR_POINT_LIGHTS];
uniform Material objectMaterial;

// Function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(ViewPosition - FragPosition);
    
    // == ======================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == ======================================
    // Phase 1: Directional lighting
    vec3 result = CalcDirLight(directional, norm, viewDir);
    // Phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(lights[i], norm, FragPosition, viewDir);
    
    color = vec4(result, 1.0);
}

// Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    
	// Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
	// Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objectMaterial.shininess);
    
	// Combine results
    //vec3 ambient = light.ambient * vec3(texture(objectMaterial.diffuse, TexCoord));
    //vec3 diffuse = light.diffuse * diff * vec3(texture(objectMaterial.diffuse, TexCoord));
    //vec3 specular = light.specular * spec * vec3(texture(objectMaterial.specular, TexCoord));
	
	vec3 ambient = light.ambient * vec3(texture(objectMaterial.diffuse2D, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(objectMaterial.diffuse2D, TexCoord));
    vec3 specular = light.specular * spec;
    
	return (ambient + diffuse + specular);
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
	// Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
	// Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objectMaterial.shininess);
	
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
	// Combine results
    //vec3 ambient = light.ambient * vec3(texture(objectMaterial.diffuse, TexCoord));
    //vec3 diffuse = light.diffuse * diff * vec3(texture(objectMaterial.diffuse, TexCoord));
    //vec3 specular = light.specular * spec * vec3(texture(objectMaterial.specular, TexCoord));
	
	vec3 ambient = light.ambient * vec3(texture(objectMaterial.diffuse2D, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(objectMaterial.diffuse2D, TexCoord));
    vec3 specular = light.specular * spec;
    
	ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
	return (ambient + diffuse + specular);
}