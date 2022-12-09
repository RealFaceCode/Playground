#ifndef GRF_H
#define GRF_H

#include "../core.h"
#include "../logger.h"

/**@brief Dont use it is not ready yet!*/
namespace GFX
{
#ifdef _DEBUG
    #define CHECK_INIT_GFX {if(!INIT){LOG_ASSERT(false, {}, "Tried to use function'%s()' but GFX::Init() is not init!", __FUNCTION__);}};
#else
    #define CHECK_INIT_GFX
#endif

    extern bool INIT;

	enum RenderApi
	{
		GL,
		VK
	};

	void Init(RenderApi api = RenderApi::GL);
}
#endif // !GRF_H
