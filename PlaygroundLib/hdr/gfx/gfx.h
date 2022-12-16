#ifndef GRF_H
#define GRF_H
#include "../core.h"
#include "../logger.h"
#include "../../hdr/window/window.h"

/**@brief Dont use it is not ready yet!*/
namespace GFX
{
	enum RenderApi
	{
		GL,
		VK
	};

	void Init(const Window::Window& window, const RenderApi& api = RenderApi::GL);
    const ui32* GetWindowWidth();
    const ui32* GetWindowHeight();
}
#endif // !GRF_H
