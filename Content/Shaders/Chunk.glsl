// @file Chunk.glsl
// @author Marco Silva (msilva2203)

//-------------------------------------------------------------------------------------------------
#vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aTextureIndex;
layout (location = 3) in float aLightLevel;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 texCoord;
out float textureIndex;
out float lightLevel;

void main()
{
    mat4 transform = uProjection * uView * uModel;
    gl_Position = transform * vec4(aPos, 1.0);

    texCoord = aTexCoord;
    textureIndex = aTextureIndex;
    lightLevel = aLightLevel;
}

//-------------------------------------------------------------------------------------------------
#fragment
#version 330 core

uniform sampler2D uTexture;

in vec2 texCoord;
in float textureIndex;
in float lightLevel;

out vec4 FragColor;

void main()
{
    int atlasSize = 4;
    vec2 atlasTextureCoord = vec2(int(textureIndex) % atlasSize, int(textureIndex) / atlasSize);
    atlasTextureCoord.y = atlasSize - atlasTextureCoord.y - 1;
    vec2 atlasCoord = texCoord / float(atlasSize);
    atlasCoord = atlasCoord + (atlasTextureCoord) / float(atlasSize);
    //atlasCoord = vec2(1 - atlasCoord.x, 1 - atlasCoord.y);
    FragColor = lightLevel * texture(uTexture, atlasCoord);
}
