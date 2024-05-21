#version 460 core

out vec2 vertex_texture_coordinates;

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture_coordinates;

void main(void)
{
	gl_Position = vec4(position, 0, 1);
	vertex_texture_coordinates = texture_coordinates;
}