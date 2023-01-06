#version 460 core
in vec2 vTexCoord;

out vec4 color;

uniform sampler2D uTexture;

void main()
{
    color =  vec4(1, 1, 1, texture2D(uTexture, vTexCoord).r) * vec4(1, 0, 0, 1);
}