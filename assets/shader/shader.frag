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
		case 0: color = fColor * texture(uTexture[0], fTexCoord); break;
		case 1: color = fColor * texture(uTexture[1], fTexCoord); break;
		case 2: color = fColor * texture(uTexture[2], fTexCoord); break;
		case 3: color = fColor * texture(uTexture[3], fTexCoord); break;
		case 4: color = fColor * texture(uTexture[4], fTexCoord); break;
		case 5: color = fColor * texture(uTexture[5], fTexCoord); break;
		case 6: color = fColor * texture(uTexture[6], fTexCoord); break;
		case 7: color = fColor * texture(uTexture[7], fTexCoord); break;
		default: discard;
	}
}