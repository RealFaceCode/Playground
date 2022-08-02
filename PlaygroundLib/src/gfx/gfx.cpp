#include "../../hdr/core.h"
#include "../../hdr/gfx/gfx.h"
#include "../../hdr/gfx/batch.h"
namespace GFX
{
    static void GLAPIENTRY GLErrorCallback( GLenum source,
                     GLenum type,
                     GLuint id,
                     GLenum severity,
                     GLsizei length,
                     const GLchar* message,
                     const void* userParam )
    {
        if(type == GL_DEBUG_TYPE_ERROR ) {
            fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                    ("** GL ERROR **"), type, severity, message);
        }
    }

	void Init(RenderApi api)
	{
		bool result = false;;
		switch (api)
		{
		case RenderApi::GL:
			result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			break;
		case RenderApi::VK:
			break;
		default:
			break;
		}

		if (!result)
		{
			log_assert(false, "Failed to init glad!");
		}

#ifdef _DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback( GLErrorCallback, 0 );
#endif

		BatchHandler::Init();
	}
}