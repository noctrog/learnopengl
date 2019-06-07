#version 450 core

void main (void)
{
	const vec2 positions[] = {
		vec2(-1.0f, 1.0f),
		vec2(-1.0f,-1.0f),
		vec2( 1.0f, 1.0f),
		vec2( 1.0f, 1.0f),
		vec2(-1.0f,-1.0f),
		vec2( 1.0f,-1.0f)
	};

	gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
}
