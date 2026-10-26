in vec4 vColor;
in float vRadius;
in vec2 vLocalCoords;
in vec2 vSize;

out vec4 FragColor;

float roundedBoxSDF(vec2 p, vec2 halfSize, float radius)
{
    vec2 q = abs(p) - halfSize + radius;

    return length(max(q, 0.0))
         + min(max(q.x, q.y), 0.0)
         - radius;
}

void main()
{
    vec2 halfSize = vSize * 0.5;

    float radius = clamp(
        vRadius,
        0.0,
        min(halfSize.x, halfSize.y)
    );

    vec2 p = (vLocalCoords - 0.5) * vSize;

    float d = roundedBoxSDF(p, halfSize, radius);

    float edgeWidth = max(fwidth(d), 1e-6);
    float alpha = 1.0 - smoothstep(0.0, edgeWidth, d);

    if (alpha <= 0.001)
        discard;

    FragColor = vec4(vColor.rgb, vColor.a * alpha);
}