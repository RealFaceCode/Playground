#ifndef shader_h
#define shader_h

namespace GFX
{
	struct Shader
	{
	public:
		unsigned int mId;
		std::vector<unsigned int> mAttachments;
		std::unordered_map<std::string, unsigned int> mLocations;

	public:
		Shader();
		void destroy();
		void bind();
		void unbind();
		bool compile(const char* shaderPath, ui32 shaderType);
		bool build();

	public:
		void setUniformMat2(const char* uniformName, glm::mat2 mat2);
		void setUniformMat3(const char* uniformName, glm::mat3 mat3);
		void setUniformMat4(const char* uniformName, glm::mat4 mat4);
		void setUniform1f(const char* uniformName, f32 f);
		void setUniform2f(const char* uniformName, f32 f0, f32 f1);
		void setUniform3f(const char* uniformName, f32 f0, f32 f1, f32 f2);
		void setUniform4f(const char* uniformName, f32 f0, f32 f1, f32 f2, f32 f3);
		void setUniform1d(const char* uniformName, f64 d);
		void setUniform2d(const char* uniformName, f64 d0, f64 d1);
		void setUniform3d(const char* uniformName, f64 d0, f64 d1, f64 d2);
		void setUniform4d(const char* uniformName, f64 d0, f64 d1, f64 d2, f64 d3);
		void setUniform1i(const char* uniformName, i32 i);
		void setUniform2i(const char* uniformName, i32 i0, i32 i1);
		void setUniform3i(const char* uniformName, i32 i0, i32 i1, i32 i2);
		void setUniform4i(const char* uniformName, i32 i0, i32 i1, i32 i2, i32 i3);
		void setUniformiv(const char* uniformName, i32* i, ui64 elements);
		void setUniform1ui(const char* uniformName, ui32 ui);
		void setUniform2ui(const char* uniformName, ui32 ui0, ui32 ui1);
		void setUniform3ui(const char* uniformName, ui32 ui0, ui32 ui1, ui32 ui2);
		void setUniform4ui(const char* uniformName, ui32 ui0, ui32 ui1, ui32 ui2, ui32 ui3);
	};

	namespace ShaderHandler
    {
	    void AddShader(const char* shaderName);
	    void AddCompileSource(const char* shaderName, const char* sourcePath, ui32 shaderType);
	    void BuildShader(const char* shaderName);
	    void BindShader(const char* shaderName);
	    Shader* GetShader(const char* shaderName);
    }
}

#endif