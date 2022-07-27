#include "../../hdr/core.h"
#include "../../hdr/gfx/gfx.h"
#include "../../hdr/gfx/batch.h"
#include <stb_image.h>
#include <stb_image_write.h>

namespace GFX
{
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

		GL_CHECK(glGenTextures(1, &mId);)
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, mId);)
		GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, internalType, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, texData);)
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);)
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);)
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);)
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);)
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0);)

		stbi_image_free(texData);
	}

	Image::Image(const char* data, ui32 width, ui32 height, ui32 comp)
		:mWidth(width), mHeight(height), mComp(comp)
	{
		if (data == nullptr)
		{
			log_error("Failed to create Texture!")
			return;
		}

		ui32 format = comp == 3 ? GL_RGB : GL_RGBA;
		ui32 internalType = comp == 3 ? GL_RGB32F : GL_RGBA32F;

		GL_CHECK(glGenTextures(1, &mId);)
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, mId);)
		GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, internalType, width, height, 0, format, GL_UNSIGNED_BYTE, data);)
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);)
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);)
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);)
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);)
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0);)

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
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, mId);)
	}

	void Image::unbind()
	{
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0);)
	}

	void Image::clear()
	{
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0);)
		GL_CHECK(glDeleteTextures(1, &mId);)
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