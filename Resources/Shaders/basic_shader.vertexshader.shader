#version 420 core

in vec4 position;
out float depth;

uniform mat4 transformation;

void main(void) {
	vec4 transformedPosition = transformation * position;
	gl_Position = transformedPosition;
	depth = transformedPosition.z;
}
