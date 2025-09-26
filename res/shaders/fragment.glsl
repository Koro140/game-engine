#version 410 core

in vec3 fragColor;
out vec4 frag_colour;

void main() {
	frag_colour = vec4( fragColor, 1.0 );
};