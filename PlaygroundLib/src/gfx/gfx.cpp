#include "../../hdr/core.h"
#include "../../hdr/logger.h"
#include "../../hdr/gfx/gfx.h"
#include "../../hdr/gfx/batch.h"
#include "../../hdr/gfx/image.h"
#include <OpenGL.h>

namespace GFX
{
    bool INIT = false;

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

    static void PreDefineImageSettings()
    {
        ImageSettingsBuilder::AddNewBuildingSettings("defaultSpriteSheetSetting");
        ImageSettingsBuilder::SetImageInternalFormat("defaultSpriteSheetSetting", ImageSettingsBuilder::ImageInternalFormat::RGBA8);
        ImageSettingsBuilder::SetImageFormat("defaultSpriteSheetSetting", ImageSettingsBuilder::ImageFormat::RGBA);
        ImageSettingsBuilder::SetImageFilterMin("defaultSpriteSheetSetting", ImageSettingsBuilder::ImageFilter::NEAREST);
        ImageSettingsBuilder::SetImageFilterMag("defaultSpriteSheetSetting", ImageSettingsBuilder::ImageFilter::NEAREST);

        ImageSettingsBuilder::AddNewBuildingSettings("defaultWhiteSetting");
        ImageSettingsBuilder::SetImageInternalFormat("defaultWhiteSetting", ImageSettingsBuilder::ImageInternalFormat::AUTO);
        ImageSettingsBuilder::SetImageFormat("defaultWhiteSetting", ImageSettingsBuilder::ImageFormat::AUTO);
    }

	void Init(RenderApi api)
	{
		bool result = false;;
		switch (api)
		{
		case RenderApi::GL:
			result = gladLoadGL(glfwGetProcAddress);
			break;
		case RenderApi::VK:
			break;
		default:
			break;
		}

		if (!result)
		{
		    LOG_ASSERT(false, {}, "Failed to init glad!");
		}
        INIT = true;

#ifdef _DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback( GLErrorCallback, 0 );
#endif
        PreDefineImageSettings();

		BatchHandler::Init();
	}
}