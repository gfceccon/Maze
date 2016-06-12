#version 330 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D FrameBuffer;
uniform float time;
uniform vec2 rOffset;
uniform vec2 gOffset;
uniform vec2 bOffset;
uniform vec2 resolution;

void main()
{

	vec2 rAbber = rOffset.xy / resolution.xy;
	vec2 gAbber = gOffset.xy / resolution.xy;
	vec2 bAbber = bOffset.xy / resolution.xy;

	mat2 rotation = mat2( cos( time ), -sin( time ), sin( time ),  cos( time ));
	rAbber = rotation * rAbber;
	gAbber = rotation * gAbber;
	bAbber = rotation * bAbber;

	vec3 final;
	final.x = texture(FrameBuffer, TexCoord + rAbber).x;
	final.y = texture(FrameBuffer, TexCoord + gAbber).y;
	final.z = texture(FrameBuffer, TexCoord + bAbber).z;

    color = vec4(final, 1.0);
}
