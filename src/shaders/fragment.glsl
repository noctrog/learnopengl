#version 450 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D smiley;

void main()
{
	vec2 new_tex_coords = TexCoord * 2;
	FragColor = mix(texture(ourTexture, new_tex_coords), texture(smiley, new_tex_coords), 0.5);
}
