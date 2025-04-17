// @author Marco Silva (msilva2203)

#vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aLightLevel;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 texCoord;
out float lightLevel;

void main()
{
    mat4 transform = uProjection * uView * uModel;
    gl_Position = transform * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    lightLevel = aLightLevel;
}

#fragment
#version 330 core

uniform sampler2D uTexture;

in vec2 texCoord;
in float lightLevel;

out vec4 FragColor;

void main()
{
    FragColor = lightLevel * texture(uTexture, texCoord);
}
