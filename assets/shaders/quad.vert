layout(location = 0) in vec4 aWorldPosition;
layout(location = 1) in vec4 aTint;
layout(location = 2) in vec2 aTextureCoords;
layout(location = 3) in float aTextureIndex;

out vec4 vTint;
out vec2 vTextureCoords;
flat out float vTextureIndex;

void main()
{
	vTint = aTint;
	vTextureCoords = aTextureCoords;
	vTextureIndex = aTextureIndex;
	gl_Position = aWorldPosition;
}
