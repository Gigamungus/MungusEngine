#version 420 core

in float depth;
out vec4 color;

void main() {
	color = vec4( 1- (-depth / 10), 0.0, 0.0, 1.0);
}
