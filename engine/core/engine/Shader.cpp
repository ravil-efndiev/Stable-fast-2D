#include "Shader.hpp"
#include "utils.hpp"

namespace s2f
{
	Shader::Shader(
		const std::filesystem::path& vertexShaderPath, 
		const std::filesystem::path& fragmentShaderPath)
	{
		mVertexShaderSource = getTextFromFile(vertexShaderPath);
		mFragmentShaderSource = getTextFromFile(fragmentShaderPath);

		mID = glCreateProgram();
		mVertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		mFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		auto statusC1 = compileShader(mVertexShaderID, mVertexShaderSource);
		auto statusC2 = compileShader(mFragmentShaderID, mFragmentShaderSource);
		auto statusL  = link();
		mValid = checkStatuses(statusC1, statusC2, statusL);

		if (!mValid) {
			deleteShaders();
			glDeleteProgram(mID);
		}
	}

	Shader::~Shader()
	{
		glDeleteProgram(mID);
	}

	Status Shader::compileShader(GLuint shaderID, const std::string& shaderSource)
	{
		glShaderSource(shaderID, 1, shaderSource.c_str(), nullptr);
		glCompileShader(shaderID);

		bool compileSuccess;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileSuccess);
		if (!compileSuccess)
		{
			constexpr i32 logBuffSize = 512;
			char log[logBuffSize];
			glGetShaderInfoLog(shaderID, logBuffSize, nullptr, log);
			return statusError("Failed to compile shader, GL log:\n" + log);
		}
		return statusSuccess();
	}

	Status Shader::link()
	{
		glAttachShader(mID, mVertexShaderID);
		glAttachShader(mID, mFragmentShaderID);
		glLinkProgram(mID);

		bool linkStatus;
		glGetProgramiv(mID, GL_LINK_STATUS, &linkStatus);
		if (!linkStatus)
		{
			constexpr i32 logBuffSize = 512;
			char log[logBuffSize];
			glGetProgramInfoLog(mID, logBuffSize, nullptr, log);
			return statusError("Failed to link shader, GL log:\n" + log);
		}

		glValidateProgram(mID);
		deleteShaders();

		return statusSuccess();
	}

	void Shader::deleteShaders()
	{
		glDeleteShader(mVertexShaderID);
		glDeleteShader(mFragmentShaderID);
	}

	GLuint Shader::id() const
	{
		return mID;
	}

	bool Shader::valid() const
	{
		return mValid;
	}
}
