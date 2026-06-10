layout(location = 0) in vec4 aWorldPosition;
layout(location = 1) in vec2 aTextureCoords;
layout(location = 2) in mat4 aTransform;
layout(location = 6) in vec4 aTint;

out vec4 vTint;
out vec2 vTextureCoords;

uniform mat4 uProjview;

void main()
{
	vTint = aTint;
	vTextureCoords = aTextureCoords;
	gl_Position = uProjview * aTransform * aWorldPosition;
}
