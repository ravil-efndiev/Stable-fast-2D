#version 450 core

layout(location = 0) in vec3 aWorldPosition;
layout(location = 1) in vec4 aTint;
layout(location = 3) in vec2 aTextureCoords;
layout(location = 3) in float aTextureIndex;

out vec4 vTint;
out vec2 vTextureCoords;
out float vTextureIndex;

void main()
{
	vTint = aTint;
	vTextureCoords = aTextureCoords;
	vTextureIndex = aTextureIndex;
	gl_Position = vec4(aWorldPosition, 1.0f);
}
