layout(location = 0) in vec4 aWorldPosition;
layout(location = 1) in vec4 aTint;
layout(location = 2) in vec2 aTextureCoords;
layout(location = 3) in float aTextureIndex;
layout(location = 4) in float aTextureType;

out vec4 vTint;
out vec2 vTextureCoords;
flat out float vTextureIndex;
flat out float vTextureType;

uniform mat4 uProjview;

void main()
{
	vTint = aTint;
	vTextureCoords = aTextureCoords;
	vTextureIndex = aTextureIndex;
	vTextureType = aTextureType;
	gl_Position = uProjview * aWorldPosition;
}
