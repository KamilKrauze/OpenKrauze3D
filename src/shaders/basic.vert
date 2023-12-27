#version 460

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;

out vec4 v_colour;

void main() {
	gl_Position = position;
	v_colour = colour;
}