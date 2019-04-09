#version 450 core

out vec4 FragColor;

in vec2 TexCoord;

in vec3 FragPos;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform sampler2D smiley;

uniform vec3 lightColor;
uniform vec3 lightPos;
layout (location = 2) uniform vec3 viewPos;

void main()
{
	float ambient_strength = 0.1f;
	float specular_strength = 0.5f;

	// ambient
	vec3 ambient = lightColor * ambient_strength;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	// specular 
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
	vec3 specular = specular_strength * spec * lightColor;

	vec2 new_tex_coords = TexCoord * 2;
	vec4 object_color = mix(texture(ourTexture, new_tex_coords), texture(smiley, new_tex_coords), 0.5);

	FragColor = vec4(ambient + diffuse + specular, 1.0f) * object_color;
}
