#version 450 core

layout(location = 0) out vec4 FragColor;

uniform sampler2DMS screen_texture;

void main(void)
{
	ivec2 coord = ivec2(gl_FragCoord.xy);
	vec4 result = vec4(0.0);
	int i;

	for (i = 0; i < 4; ++i) {
		result += texelFetch(screen_texture, coord, i);
	}
	result = result / 4;

	FragColor = vec4(result.xyz, 1.0);
}
