#version 420 core

in float depth;
out vec4 color;

void main() {
	color = vec4( 1- (-depth / 50), 0.0, (-depth / 50), 1.0);
}
