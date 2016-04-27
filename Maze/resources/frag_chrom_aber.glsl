#version 330 core

in vec2 tex_coord;
out vec4 color;

uniform sampler2D texture2D;
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
	final.x = texture(texture2D, tex_coord + rAbber).x;
	final.y = texture(texture2D, tex_coord + gAbber).y;
	final.z = texture(texture2D, tex_coord + bAbber).z;
	final = clamp(final, vec3(0.0,0.0,0.0), vec3(1,1,1));
    color = vec4(final, 1.0);
}