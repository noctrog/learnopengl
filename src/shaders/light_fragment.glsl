#version 450 core

out vec4 aColor;

uniform vec3 lightColor;

void main(void)
{
	aColor = vec4(lightColor, 1.0f);
}
