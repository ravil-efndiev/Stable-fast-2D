#pragma once
#include "include.hpp"
#include "status.hpp"

namespace s2f
{
	struct GLState;
	class Shader
	{
	private:
		using Path = std::filesystem::path;

	public:
		Shader() = default;
		Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		Shader(const Path& vertexShaderPath, const Path& fragmentShaderPath);

		void create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		void create(const Path& vertexShaderPath, const Path& fragmentShaderPath);

		~Shader();

		void setUniformMat4(
			const char* name, const glm::mat4& mat, GLState* glState = nullptr
		) const;
		void setUniformIntArray(
			const char* name, size_t size, const i32* values, GLState* glState = nullptr
		) const;

		GLuint id() const { return mID; }
		bool valid() const { return mValid; }

	private:
		void init();
		Status compileShader(GLuint shaderID, const char* shaderSource);
		Status link();

		void deleteShaders();
		void bind(GLState* glState) const;

	private:
		std::string mVertexShaderSource;
		std::string mFragmentShaderSource;
		GLuint mID{ 0 };
		GLuint mVertexShaderID{ 0 };
		GLuint mFragmentShaderID{ 0 };
		bool mValid{ false };
	};
}
