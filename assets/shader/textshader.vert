#version 460 core
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform mat4 uProj;

void main()
{
    gl_Position = uProj * vec4(aPosition, 0.0, 1.0);
    vTexCoord = aTexCoord;
}