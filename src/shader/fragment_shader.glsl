#version 460 core

out vec4 fragCol;
in vec2 texCoords;

uniform sampler2D image;

void main() {
	fragCol = texture(image, texCoords) * vec4(0.2, 0.5, 0.6, 1.0);
}
