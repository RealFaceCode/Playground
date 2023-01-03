#version 460 core
layout(location = 0) in vec2 aPosition;

uniform mat4 uProj;

void main()
{
	gl_Position = uProj * vec4(aPosition, 0.0, 1.0);

}