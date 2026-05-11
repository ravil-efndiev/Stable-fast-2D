#pragma once
#include "include.hpp"
#include "status.hpp"

namespace s2f
{
	class Shader
	{
	public:
		Shader(
			const std::filesystem::path& vertexShaderPath, 
			const std::filesystem::path& fragmentShaderPath
		);

		~Shader();

		GLuint id() const;
		bool valid() const;

	private:
		Status compileShader(GLuint shaderID, const std::string& shaderSource);
		Status link();

		void deleteShaders();

	private:
		std::string mVertexShaderSource;
		std::string mFragmentShaderSource;
		GLuint mID{ 0 };
		GLuint mVertexShaderID{ 0 };
		GLuint mFragmentShaderID{ 0 };
		bool mValid = false;
	};
}
