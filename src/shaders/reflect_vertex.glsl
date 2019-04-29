#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Position;
out vec3 Normal;

layout (location = 1) uniform mat4 model;
layout (location = 0) uniform mat4 vp;

void main(void)
{
	Normal = mat3(transpose(inverse(model))) * aNormal;
	Position = vec3(model * vec4(aPos, 1.0));
	gl_Position = vp * model * vec4(aPos, 1.0);
}
