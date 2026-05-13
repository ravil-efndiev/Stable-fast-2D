#version 450 core

in vec4 vTint;
in vec2 vTextureCoords;
in float vTextureIndex;

out vec4 FragColor;

uniform sampler2D vTextures[16];

void main() 
{
	FragColor = texture(uTextures[int(vTextureIndex)], vTextureCoords) * vTint;
}
