// @author Marco Silva (msilva2203)

#vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 uTransform;

out vec3 vertexColor;
out vec2 texCoord;

void main()
{
    gl_Position = uTransform * vec4(aPos, 1.0);
    vertexColor = aColor;
    texCoord = aTexCoord;
}

#fragment
#version 330 core

uniform sampler2D uTexture;

in vec3 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

void main()
{
    //FragColor = vec4(vertexColor * colorMult, 1.0);
    FragColor = texture(uTexture, texCoord);
}
