#version 450 core

layout(location = 0) in vec3 aWorldPosition;
layout(location = 1) in vec4 aTint;

out vec4 vTint;

void main()
{
	vTint = aTint;
	gl_Position = vec4(aWorldPosition, 1.0f);
}
