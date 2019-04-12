#version 450 core

layout (location = 0) in vec3 aPos;

layout (location = 0) uniform mat4 vp;
layout (location = 1) uniform mat4 m;

void main(void)
{
	gl_Position = vp * m * (vec4(0.2f, 0.2f, 0.2f, 1.0f) * vec4(aPos, 1.0f));
}
