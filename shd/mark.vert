#version 460 core

uniform uint width;
uniform uint height;

layout (location = 0) in vec2 position;

void main(void)
{
	gl_Position = vec4(position, 0, 1);
}