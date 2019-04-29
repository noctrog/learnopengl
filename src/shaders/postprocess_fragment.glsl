#version 450 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screen_texture;

const float offset = 1.0 / 1000.0f;

void main(void)
{
	FragColor = texture(screen_texture, TexCoords);
}

//void main(void)
//{
	//vec2 offsets[9] = vec2[](
		//vec2(-offset, offset),	// top left
		//vec2(0.0f, offset),	// top center
		//vec2(offset, offset),	// top right
		//vec2(-offset, 0.0f),	// center left
		//vec2(0.0f, 0.0f),	// center center
		//vec2(offset, 0.0f),	// center right
		//vec2(-offset, -offset),	// bottom left
		//vec2(0.0f, -offset),	// bottom center
		//vec2(offset, -offset)	// bottom right
	//);

	//float blur_kernel[9] = {
		//1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0,
		//2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0,
		//1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0
	//};

	//float kernel[9] = {
		//1.0f, 1.0f, 1.0f,
		//1.0f, -8.0f, 1.0f,
		//1.0f, 1.0f, 1.0f
	//};

	//vec3 sampleTex[9];
	//for (int i = 0; i < 9; ++i) {
		//sampleTex[i] = vec3(texture(screen_texture, TexCoords.st + offsets[i]));
	//}
	//vec3 col = vec3(0.0);
	//for (int i = 0; i < 9; ++i) {
		//col +=sampleTex[i] * kernel[i];
	//}

	//FragColor = vec4(col, 1.0);
//}
