in vec4 vTint;
in vec2 vTextureCoords;
flat in float vTextureIndex;

out vec4 FragColor;

uniform sampler2D uTextures[MAX_TEXTURE_SLOTS];

void main() 
{
	FragColor = vTextureIndex == 0.0 ? vTint : texture(uTextures[int(vTextureIndex)], vTextureCoords) * vTint;
}
