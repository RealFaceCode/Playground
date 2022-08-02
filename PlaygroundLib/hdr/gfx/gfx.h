#ifndef GRF_H
#define GRF_H

#include "../core.h"

namespace GFX
{
	enum RenderApi
	{
		GL,
		VK
	};

	void Init(RenderApi api = RenderApi::GL);
}
#endif // !GRF_H
