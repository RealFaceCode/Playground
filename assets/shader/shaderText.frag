#version 460 core
in vec2 fTexCoord;
in vec4 fColor;
in float fTextureId;

out vec4 color;

uniform sampler2D uTexture[8];

void main()
{
	switch (int(fTextureId))
	{
		case 0: color = vec4(1, 1, 1, texture2D(uTexture[0], fTexCoord).r) * fColor; break;
		case 1: color = vec4(1, 1, 1, texture2D(uTexture[1], fTexCoord).r) * fColor; break;
		case 2: color = vec4(1, 1, 1, texture2D(uTexture[2], fTexCoord).r) * fColor; break;
		case 3: color = vec4(1, 1, 1, texture2D(uTexture[3], fTexCoord).r) * fColor; break;
		case 4: color = vec4(1, 1, 1, texture2D(uTexture[4], fTexCoord).r) * fColor; break;
		case 5: color = vec4(1, 1, 1, texture2D(uTexture[5], fTexCoord).r) * fColor; break;
		case 6: color = vec4(1, 1, 1, texture2D(uTexture[6], fTexCoord).r) * fColor; break;
		case 7: color = vec4(1, 1, 1, texture2D(uTexture[7], fTexCoord).r) * fColor; break;
		default: discard;
	}
}