#version 450 core
#define NR_POINT_LIGHTS 4

out vec4 FragColor;

in vec2 TexCoord;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
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

uniform Material material;
uniform DirLight dir_light;
uniform PointLight point_light[NR_POINT_LIGHTS];

vec3 calc_dir_light(DirLight light, vec3 normal, vec3 viewDir)
{
	// Ambient light
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	// Diffuse light
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, TexCoord));

	// Specular light
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular, TexCoord));

	return (ambient + diffuse + specular);
}

vec3 calc_point_light(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	// Ambient light
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	// Diffuse
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, TexCoord));

	// Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular, TexCoord));

	// Attenuation
	float d = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + d * light.linear + d * d * light.quadratic);

	return (ambient + diffuse + specular) * attenuation;
}

void main()
{
	// properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// Directional light
	vec3 result = calc_dir_light(dir_light, norm, viewDir);

	// Point lights
	for (int i = 0; i < NR_POINT_LIGHTS; ++i) {
		result += calc_point_light(point_light[i], norm, FragPos, viewDir);
	}
	FragColor = vec4(result, 1.0);
}
