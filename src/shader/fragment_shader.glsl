#version 460 core

out vec4 fragCol;
in vec2 texCoords;

uniform sampler2D image;
uniform vec3 color;

void main() {
	fragCol = texture(image, texCoords);// * vec4(color, 1.0);
}
