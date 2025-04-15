// @author Marco Silva (msilva2203)

#vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 texCoord;

void main()
{
    mat4 transform = uProjection * uView * uModel;
    gl_Position = transform * vec4(aPos, 1.0);
    texCoord = aTexCoord;
}

#fragment
#version 330 core

uniform sampler2D uTexture;

in vec2 texCoord;

out vec4 FragColor;

void main()
{
    FragColor = texture(uTexture, texCoord);
}
