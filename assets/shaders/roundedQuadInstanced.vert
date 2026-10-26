layout(location = 0) in vec4 aWorldPosition;
layout(location = 2) in mat4 aTransform;
layout(location = 6) in vec4 aColor;
layout(location = 7) in float aRadius;

out vec4 vColor;
out float vRadius;
out vec2 vLocalCoords;
out vec2 vSize;

uniform mat4 uProjview;

void main()
{
	vColor = aColor;
	vRadius = aRadius;
    vLocalCoords = aWorldPosition.xy + 0.5;
    vSize = vec2(
        length(aTransform[0].xyz),
        length(aTransform[1].xyz)
    );
	gl_Position = uProjview * aTransform * aWorldPosition;
}
