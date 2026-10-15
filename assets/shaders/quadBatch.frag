#define TEX_RGB 0.0
#define TEX_RED 1.0

in vec4 vTint;
in vec2 vTextureCoords;
flat in float vTextureIndex;
flat in float vTextureType;

out vec4 FragColor;

uniform sampler2D uTextures[MAX_TEXTURE_SLOTS];

void main() 
{
    if (vTextureType == TEX_RGB) 
    {
	    FragColor = vTextureIndex == 0.0 ? vTint : texture(uTextures[int(vTextureIndex)], vTextureCoords) * vTint;
    }
    else if (vTextureType == TEX_RED) 
    {
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uTextures[int(vTextureIndex)], vTextureCoords).r);
        FragColor = vec4(vTint.rgb, 1.0) * sampled;
    }
}
