#include "Shader.hpp"
#include "GLState.hpp"
#include "utils.hpp"

namespace s2f
{
	Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
	{
		create(vertexShaderSource, fragmentShaderSource);
	}

	Shader::Shader(const Path& vertexShaderPath, const Path& fragmentShaderPath)
	{
		create(vertexShaderPath, fragmentShaderPath);
	}

	Shader::~Shader()
	{
		glDeleteProgram(mID);
		S2F_INFO("Deleted shader with ID " << mID);
	}

	void Shader::create(const Path& vertexShaderPath, const Path& fragmentShaderPath)
	{
		mVertexShaderSource = getTextFromFile(vertexShaderPath);
		mFragmentShaderSource = getTextFromFile(fragmentShaderPath);
		init();
	}

	void Shader::create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
	{
		mVertexShaderSource = vertexShaderSource;
		mFragmentShaderSource = fragmentShaderSource;
		init();
	}

	void Shader::init()
	{
		mID = glCreateProgram();
		mVertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		mFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		auto statusC1 = compileShader(mVertexShaderID, mVertexShaderSource.c_str());
		auto statusC2 = compileShader(mFragmentShaderID, mFragmentShaderSource.c_str());
		auto statusL = link();
		mValid = checkStatuses(statusC1, statusC2, statusL);

		if (!mValid) {
			deleteShaders();
			glDeleteProgram(mID);
		}

		S2F_INFO("Created shader with ID " << mID << " (valid = " << mValid << ")");
	}

	Status Shader::compileShader(GLuint shaderID, const char* shaderSource)
	{
		glShaderSource(shaderID, 1, &shaderSource, nullptr);
		glCompileShader(shaderID);

		GLint compileSuccess;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileSuccess);
		if (!compileSuccess)
		{
			constexpr i32 logBuffSize = 512;
			char log[logBuffSize];
			glGetShaderInfoLog(shaderID, logBuffSize, nullptr, log);
			return statusError(std::string("Failed to compile shader, GL log:\n") + log);
		}
		return statusSuccess();
	}

	Status Shader::link()
	{
		glAttachShader(mID, mVertexShaderID);
		glAttachShader(mID, mFragmentShaderID);
		glLinkProgram(mID);

		GLint linkStatus;
		glGetProgramiv(mID, GL_LINK_STATUS, &linkStatus);
		if (!linkStatus)
		{
			constexpr i32 logBuffSize = 512;
			char log[logBuffSize];
			glGetProgramInfoLog(mID, logBuffSize, nullptr, log);
			return statusError(std::string("Failed to link shader, GL log:\n") + log);
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

	void Shader::bind(GLState* glState) const
	{
		if (glState)
		{
			glState->bindShader(*this);
		}
		else
		{
			glUseProgram(mID);
		}
	}

	void Shader::setUniformMat4(
		const char* name, const glm::mat4& mat, GLState* glState
	) const {
		bind(glState);
		GLint location = glGetUniformLocation(mID, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::setUniformIntArray(
		const char* name, size_t size, const i32* values, GLState* glState
	) const {
		bind(glState);
		GLint location = glGetUniformLocation(mID, name);
		glUniform1iv(location, size, values);
	}
}
