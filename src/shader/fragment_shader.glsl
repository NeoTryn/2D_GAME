#version 460 core

out vec4 fragCol;
in vec2 texCoords;

uniform sampler2D image;
uniform vec3 color;

void main() {
	vec4 texColor = texture(image, texCoords);// * vec4(color, 1.0);

	if (texColor.a < 0.1) {
		discard;
	}

	fragCol = texColor;
}
