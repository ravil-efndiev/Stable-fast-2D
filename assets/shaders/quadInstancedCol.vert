layout(location = 0) in vec4 aWorldPosition;
layout(location = 2) in mat4 aTransform;
layout(location = 6) in vec4 aColor;

out vec4 vColor;

uniform mat4 uProjview;

void main()
{
	vColor = aColor;
	gl_Position = uProjview * aTransform * aWorldPosition;
}
