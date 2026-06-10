in vec4 vTint;
in vec2 vTextureCoords;

out vec4 FragColor;

uniform sampler2D uTextureIndex;

void main() 
{
	FragColor = texture(uTextureIndex, vTextureCoords) * vTint;
}
