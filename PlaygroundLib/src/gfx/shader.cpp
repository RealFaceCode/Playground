#include "../../hdr/core.h"
#include "../../hdr/gfx/shader.h"
#include "../../hdr/gfx/gfx.h"

namespace GFX
{
	Shader::Shader()
	{
        mId = glCreateProgram();
	}

	void Shader::destroy()
	{
		glDeleteProgram(mId);
	}

	void Shader::bind()
	{
		glUseProgram(mId);
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	bool Shader::compile(const char* shaderPath, ui32 shaderType)
	{
		FHandle::File source(shaderPath, FILE_READ);

		if (source.getData() == nullptr)
		{
			log_error("Failed to load shader");
			return false;
		}

		unsigned int shaderId = glCreateShader(shaderType);
		source.addUI8('\0');
		char const* string = (char const*)source.getData();
		glShaderSource(shaderId, 1, &string, 0);
		glCompileShader(shaderId);

		char buffer[8192];
		GLsizei length = 0;
		glGetShaderInfoLog(shaderId, sizeof(buffer), &length, buffer);
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

		for (unsigned int shaderId : mAttachments)
		{
			glAttachShader(mId, shaderId);
		}

		glLinkProgram(mId);

		char buffer[8192];
		GLsizei length = 0;
		glGetProgramInfoLog(mId, sizeof(buffer), &length, buffer);
		if (length)
		{
			log_fmt_error("Failed to build shader: '%s'", buffer);
			return false;
		}

		for (unsigned int shaderId : mAttachments)
		{
			glDetachShader(mId, shaderId);
			glDeleteShader(shaderId);
		}

		mAttachments.clear();

		bind();

		int numUniforms;
		glGetProgramiv(mId, GL_ACTIVE_UNIFORMS, &numUniforms);

		int maxCharLen;
		glGetProgramiv(mId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxCharLen);

		if (numUniforms > 0 && maxCharLen > 0)
		{
			char* buffer = new char[maxCharLen];

			for (int i = 0; i < numUniforms; i++)
			{
				int len, size;
				GLenum dataType;
				glGetActiveUniform(mId, i, maxCharLen, &len, &size, &dataType, buffer);
				unsigned int loc = glGetUniformLocation(mId, buffer);
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
			glUniformMatrix4fv(mLocations.at(uniformName), 1, GL_FALSE, &mat2[0][0]);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniformMat3(const char* uniformName, glm::mat3 mat3)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniformMatrix4fv(mLocations.at(uniformName), 1, GL_FALSE, &mat3[0][0]);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniformMat4(const char* uniformName, glm::mat4 mat4)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniformMatrix4fv(mLocations.at(uniformName), 1, GL_FALSE, &mat4[0][0]);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform1f(const char* uniformName, f32 f)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform1f(mLocations.at(uniformName), f);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform2f(const char* uniformName, f32 f0, f32 f1)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform2f(mLocations.at(uniformName), f0, f1);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform3f(const char* uniformName, f32 f0, f32 f1, f32 f2)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform3f(mLocations.at(uniformName), f0, f1, f2);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform4f(const char* uniformName, f32 f0, f32 f1, f32 f2, f32 f3)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform4f(mLocations.at(uniformName), f0, f1, f2, f3);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform1d(const char* uniformName, f64 d)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform1d(mLocations.at(uniformName), d);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform2d(const char* uniformName, f64 d0, f64 d1)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform2d(mLocations.at(uniformName), d0, d1);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform3d(const char* uniformName, f64 d0, f64 d1, f64 d2)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform3d(mLocations.at(uniformName), d0, d1, d2);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform4d(const char* uniformName, f64 d0, f64 d1, f64 d2, f64 d3)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform4d(mLocations.at(uniformName), d0, d1, d2, d3);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform1i(const char* uniformName, i32 i)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform1i(mLocations.at(uniformName), i);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform2i(const char* uniformName, i32 i0, i32 i1)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform2i(mLocations.at(uniformName), i0, i1);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform3i(const char* uniformName, i32 i0, i32 i1, i32 i2)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform3i(mLocations.at(uniformName), i0, i1, i2);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform4i(const char* uniformName, i32 i0, i32 i1, i32 i2, i32 i3)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform4i(mLocations.at(uniformName), i0, i1, i2, i3);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniformiv(const char* uniformName, i32* i, ui64 elements)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform1iv(mLocations.at(uniformName), elements, &i[0]);
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
			glUniform1ui(mLocations.at(uniformName), ui);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform2ui(const char* uniformName, ui32 ui0, ui32 ui1)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform2ui(mLocations.at(uniformName), ui0, ui1);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform3ui(const char* uniformName, ui32 ui0, ui32 ui1, ui32 ui2)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform3ui(mLocations.at(uniformName), ui0, ui1, ui2);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}

	void Shader::setUniform4ui(const char* uniformName, ui32 ui0, ui32 ui1, ui32 ui2, ui32 ui3)
	{
		if (mLocations.find(uniformName) != mLocations.end())
		{
			glUniform4ui(mLocations.at(uniformName), ui0, ui1, ui2, ui3);
		}
        else
        {
            log_fmt_assert(false ,"Uniform not found: '%s'", uniformName);
        }
	}
}