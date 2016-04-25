#version 330

in vec2 TexCoor;
out vec4 fColour;

uniform sampler2D text;
uniform vec4 spriteColour;

void main(void) {
	fColour = spriteColour * texture(text, TexCoor);
}