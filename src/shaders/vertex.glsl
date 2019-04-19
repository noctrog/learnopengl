#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

out vec3 FragPos;
out vec3 Normal;

layout (location = 1) uniform mat4 model;
layout (location = 0) uniform mat4 vp;

void main()
{
    gl_Position = vp * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0f));
}
