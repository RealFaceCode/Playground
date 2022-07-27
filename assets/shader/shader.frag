#version 460 core
in vec2 fTexCoord;
in vec4 fColor;
in flat int fTextureId;

out vec4 color;

uniform sampler2D uTexture[8];

void main()
{
	switch (int(fTextureId))
	{
		case 0: color = texture(uTexture[0], fTexCoord) * fColor; break;
		case 1: color = texture(uTexture[1], fTexCoord) * fColor; break;
		case 2: color = texture(uTexture[2], fTexCoord) * fColor; break;
		case 3: color = texture(uTexture[3], fTexCoord) * fColor; break;
		case 4: color = texture(uTexture[4], fTexCoord) * fColor; break;
		case 5: color = texture(uTexture[5], fTexCoord) * fColor; break;
		case 6: color = texture(uTexture[6], fTexCoord) * fColor; break;
		case 7: color = texture(uTexture[7], fTexCoord) * fColor; break;
		default: discard;
	}
}