#version 460 core
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTexureId;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

out vec2 fTexCoord;
out vec4 fColor;
out float fTextureId;

void main()
{
	gl_Position = uModel * uView * uProj * vec4(aPosition, 0.0, 1.0);
	fColor = aColor;
	fTexCoord = aTexCoord;
	fTextureId = aTexureId;
}