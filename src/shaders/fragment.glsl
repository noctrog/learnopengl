#version 450 core

out vec4 FragColor;

in vec2 TexCoord;

in vec3 FragPos;
in vec3 Normal;

layout (location = 2) uniform vec3 viewPos;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	//vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform Light light;

void main()
{
	// ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	//vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, TexCoord));

	// specular 
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = vec3(texture(material.specular, TexCoord)) * spec * light.specular;

	float d = length(FragPos - light.position);
	float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * d * d);

	FragColor = attenuation * vec4(ambient + diffuse + specular, 1.0f);
}
