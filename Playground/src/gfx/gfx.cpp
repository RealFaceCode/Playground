#include "../../hdr/core.h"
#include "../../hdr/gfx/gfx.h"
#include "../../hdr/gfx/batch.h"
#include <stb_image.h>
#include <stb_image_write.h>

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

	Image::Image(const char* path)
	{
		unsigned char* texData = stbi_load(path, &mWidth, &mHeight, &mComp, 0);
		if (texData == nullptr)
		{
			log_fmt_error("Failed to create Texture with path'%s'", path);
			return;
		}


		ui32 format = mComp == 3 ? GL_RGB : GL_RGBA;
		ui32 internalType = mComp == 3 ? GL_RGB32F : GL_RGBA32F;

		glGenTextures(1, &mId);
		glBindTexture(GL_TEXTURE_2D, mId);
		glTexImage2D(GL_TEXTURE_2D, 0, internalType, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, texData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(texData);
	}

	Image::Image(const unsigned char* data, ui32 width, ui32 height, ui32 comp)
		:mWidth(width), mHeight(height), mComp(comp)
	{
		if (data == nullptr)
		{
			log_error("Failed to create Texture!")
			return;
		}

		ui32 format = GL_RGBA;
		ui32 internalType = GL_RGBA8;

		glGenTextures(1, &mId);
		glBindTexture(GL_TEXTURE_2D, mId);
		glTexImage2D(GL_TEXTURE_2D, 0, internalType, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	Image::Image(const Image& image)
	{
		mId = image.mId;
		mWidth = image.mWidth;
		mHeight = image.mHeight;
		mComp = image.mComp;
	}

	void Image::bind()
	{
		glBindTexture(GL_TEXTURE_2D, mId);
	}

	void Image::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Image::clear()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &mId);
	}

	Image& Image::operator=(const Image& other)
	{
		mId = other.mId;
		mWidth = other.mWidth;
		mHeight = other.mHeight;
		mComp = other.mComp;
		return *this;
	}
}