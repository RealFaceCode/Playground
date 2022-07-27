#ifndef GRF_H
#define GRF_H

namespace GFX
{
#define GL_CHECK(gl_func) gl_func; { int err = glGetError(); if(err != GL_NO_ERROR){log_fmt_error("OpenGL error: '%i'", err);}}

	enum RenderApi
	{
		GL,
		VK
	};

	void Init(RenderApi api = RenderApi::GL);

	struct Image
	{
	public:
		ui32 mId;
		i32 mWidth;
		i32 mHeight;
		i32 mComp;

		Image() = default;
		Image(const char* path);
		Image(const unsigned char* data, ui32 width, ui32 height, ui32 comp);
		Image(const Image& image);
		~Image() = default;

		void bind();
		void unbind();

		void clear();

		Image& operator=(const Image& other);
	};

}

#endif // !GRF_H
