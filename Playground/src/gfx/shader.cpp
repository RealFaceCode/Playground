#include "../../hdr/core.h"
#include "../../hdr/gfx/shader.h"
#include "../../hdr/gfx/gfx.h"

namespace GFX
{
	Shader::Shader()
	{}

	void Shader::destroy()
	{
		GL_CHECK(glDeleteProgram(mId);)
	}

	void Shader::bind()
	{
		GL_CHECK(glUseProgram(mId);)
	}

	void Shader::unbind()
	{
		GL_CHECK(glUseProgram(0);)
	}

	bool Shader::compile(const char* shaderPath, ui32 shaderType)
	{
		FHandle::File source(shaderPath, FILE_READ);

		if (source.getData() == nullptr)
		{
			log_error("Failed to load shader");
			return false;
		}

		unsigned int shaderId = GL_CHECK(glCreateShader(shaderType);)
		source.addUI8('\0');
		char const* string = (char const*)source.getData();
		GL_CHECK(glShaderSource(shaderId, 1, &string, 0);)
		GL_CHECK(glCompileShader(shaderId);)

		char buffer[8192];
		GLsizei length = 0;
		GL_CHECK(glGetShaderInfoLog(mId, sizeof(buffer), &length, buffer);)
		if (length)
		{
			log_fmt_assert(false, "Failed to build shader: '%s'", buffer);
			return false;
		}

		mAttachments.emplace_back(shaderId);

		return true;
	}

	bool Shader::build()
	{
		if (mAttachments.empty())
		{
			return false;
		}

		mId = GL_CHECK(glCreateProgram();)

		for (unsigned int shaderId : mAttachments)
		{
			GL_CHECK(glAttachShader(mId, shaderId);)
		}

		GL_CHECK(glLinkProgram(mId);)

		char buffer[8192];
		GLsizei length = 0;
		GL_CHECK(glGetShaderInfoLog(mId, sizeof(buffer), &length, buffer);)
		if (length)
		{
			log_fmt_error("Failed to build shader: '%s'", buffer);
			return false;
		}

		for (unsigned int shaderId : mAttachments)
		{
			GL_CHECK(glDetachShader(mId, shaderId);)
			GL_CHECK(glDeleteShader(shaderId);)
		}

		mAttachments.clear();

		bind();

		int numUniforms;
		GL_CHECK(glGetProgramiv(mId, GL_ACTIVE_UNIFORMS, &numUniforms);)

		int maxCharLen;
		GL_CHECK(glGetProgramiv(mId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxCharLen);)

		if (numUniforms > 0 && maxCharLen > 0)
		{
			char* buffer = new char[maxCharLen];

			for (int i = 0; i < numUniforms; i++)
			{
				int len, size;
				GLenum dataType;
				GL_CHECK(glGetActiveUniform(mId, i, maxCharLen, &len, &size, &dataType, buffer);)
				unsigned int loc = GL_CHECK(glGetUniformLocation(mId, buffer);)
				mLocations[buffer] = loc;
			}

			delete[] buffer;
		}

		return true;
	}

	void Shader::setUniformMat2(const char* uniformName, glm::mat2 mat2)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniformMatrix4fv(mLocations.at(uniformName), 1, GL_FALSE, &mat2[0][0]);)
		}
	}

	void Shader::setUniformMat3(const char* uniformName, glm::mat3 mat3)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniformMatrix4fv(mLocations.at(uniformName), 1, GL_FALSE, &mat3[0][0]);)
		}
	}

	void Shader::setUniformMat4(const char* uniformName, glm::mat4 mat4)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniformMatrix4fv(mLocations.at(uniformName), 1, GL_FALSE, &mat4[0][0]);)
		}
	}

	void Shader::setUniform1f(const char* uniformName, f32 f)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform1f(mLocations.at(uniformName), f);)
		}
	}

	void Shader::setUniform2f(const char* uniformName, f32 f0, f32 f1)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform2f(mLocations.at(uniformName), f0, f1);)
		}
	}

	void Shader::setUniform3f(const char* uniformName, f32 f0, f32 f1, f32 f2)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform3f(mLocations.at(uniformName), f0, f1, f2);)
		}
	}

	void Shader::setUniform4f(const char* uniformName, f32 f0, f32 f1, f32 f2, f32 f3)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform4f(mLocations.at(uniformName), f0, f1, f2, f3);)
		}
	}

	void Shader::setUniform1d(const char* uniformName, f64 d)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform1d(mLocations.at(uniformName), d);)
		}
	}

	void Shader::setUniform2d(const char* uniformName, f64 d0, f64 d1)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform2d(mLocations.at(uniformName), d0, d1);)
		}
	}

	void Shader::setUniform3d(const char* uniformName, f64 d0, f64 d1, f64 d2)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform3d(mLocations.at(uniformName), d0, d1, d2);)
		}
	}

	void Shader::setUniform4d(const char* uniformName, f64 d0, f64 d1, f64 d2, f64 d3)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform4d(mLocations.at(uniformName), d0, d1, d2, d3);)
		}
	}

	void Shader::setUniform1i(const char* uniformName, i32 i)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform1i(mLocations.at(uniformName), i);)
		}
	}

	void Shader::setUniform2i(const char* uniformName, i32 i0, i32 i1)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform2i(mLocations.at(uniformName), i0, i1);)
		}
	}

	void Shader::setUniform3i(const char* uniformName, i32 i0, i32 i1, i32 i2)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform3i(mLocations.at(uniformName), i0, i1, i2);)
		}
	}

	void Shader::setUniform4i(const char* uniformName, i32 i0, i32 i1, i32 i2, i32 i3)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform4i(mLocations.at(uniformName), i0, i1, i2, i3);)
		}
	}

	void Shader::setUniformiv(const char* uniformName, i32* i, ui64 elements)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform1iv(mLocations.at(uniformName), elements, &i[0]);)
		}
		else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform1ui(const char* uniformName, ui32 ui)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform1ui(mLocations.at(uniformName), ui);)
		}
	}

	void Shader::setUniform2ui(const char* uniformName, ui32 ui0, ui32 ui1)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform2ui(mLocations.at(uniformName), ui0, ui1);)
		}
	}

	void Shader::setUniform3ui(const char* uniformName, ui32 ui0, ui32 ui1, ui32 ui2)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform3ui(mLocations.at(uniformName), ui0, ui1, ui2);)
		}
	}

	void Shader::setUniform4ui(const char* uniformName, ui32 ui0, ui32 ui1, ui32 ui2, ui32 ui3)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			GL_CHECK(glUniform4ui(mLocations.at(uniformName), ui0, ui1, ui2, ui3);)
		}
	}
}