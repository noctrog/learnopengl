#version 450 core

out vec4 FragColor;

in vec2 TexCoord;

in vec3 FragPos;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform sampler2D smiley;

layout (location = 2) uniform vec3 viewPos;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
	// ambient
	vec3 ambient = light.ambient * material.ambient;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * light.diffuse * material.diffuse;

	// specular 
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = material.specular * spec * light.specular;

	// texture
	vec2 new_tex_coords = TexCoord * 2;
	vec4 object_color = mix(texture(ourTexture, new_tex_coords), texture(smiley, new_tex_coords), 0.5);

	FragColor = vec4(ambient + diffuse + specular, 1.0f) * object_color;
}
