#include "Shader.hpp"
#include "GLState.hpp"
#include "utils.hpp"
#include "GLAPI.hpp"
#include "Engine.hpp"

namespace s2f
{
	Shader::Shader(std::string_view vertexShaderSource, std::string_view fragmentShaderSource, bool useStandardHeader)
	{
		create(vertexShaderSource, fragmentShaderSource, useStandardHeader);
	}

	Shader::Shader(const Path& vertexShaderPath, const Path& fragmentShaderPath, bool useStandardHeader)
	{
		create(vertexShaderPath, fragmentShaderPath, useStandardHeader);
	}

	Shader::~Shader()
	{
		Engine::get()->renderer().glState().invalidateShader();
		glDeleteProgram(mID);
		Logger::infoVerbose("Deleted shader with ID {}", mID);
	}

	void Shader::create(const Path& vertexShaderPath, const Path& fragmentShaderPath, bool useStandardHeader)
	{
		mVertexShaderSource = getTextFromFile(vertexShaderPath);
		mFragmentShaderSource = getTextFromFile(fragmentShaderPath);
		mUseStandardHeader = useStandardHeader;
		init();
	}

	void Shader::create(std::string_view vertexShaderSource, std::string_view fragmentShaderSource, bool useStandardHeader)
	{
		mVertexShaderSource = vertexShaderSource;
		mFragmentShaderSource = fragmentShaderSource;
		mUseStandardHeader = useStandardHeader;
		init();
	}

	void Shader::init()
	{
		if (mUseStandardHeader)
		{
			std::string header = getStandardHeader();
			auto maxTextureSlots = glapi::getMaxTextureSlots();
			std::string fragmentShaderHeader
				= (header + "#define MAX_TEXTURE_SLOTS ") + std::to_string(maxTextureSlots) + "\n";

			mVertexShaderSource = header + mVertexShaderSource;
			mFragmentShaderSource = fragmentShaderHeader + mFragmentShaderSource;
		}

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

		Logger::infoVerbose("Created shader with ID {}, valid = {}", mID, mValid);
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

	std::string Shader::getStandardHeader() const
	{
		auto glVersion = Engine::get()->window().openglVersion();
		return std::string("#version ") + getVersionStringGLSL(glVersion) + "core\n";
	}
}
