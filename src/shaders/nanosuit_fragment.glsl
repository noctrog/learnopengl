#version 450 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
void main(void)
{
	FragColor = texture(texture_diffuse1, TexCoord);
	FragColor.a = 1.0f;
}
