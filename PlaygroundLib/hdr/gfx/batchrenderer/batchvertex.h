#ifndef __BATCHVERTEX_H__
#define __BATCHVERTEX_H__
#include "../../core.h"
namespace GFX
{
	struct BatchVertex2D
	{
	public:
		glm::vec2 mPosition;
		glm::vec4 mColor;
		glm::vec2 mTexCoord;
	    f32 mTexture;
	};

	struct BatchVertex3D
	{
	public:
		glm::vec3 mPosition;
		glm::vec4 mColor;
		glm::vec2 mTexCoord;
	    f32 mTexture;
	};
}
#endif // __BATCHVERTEX_H__