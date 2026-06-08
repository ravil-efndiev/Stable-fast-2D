#pragma once
#include "include.hpp"

namespace s2f
{
	std::string getTextFromFile(const std::filesystem::path& path);

	// gets string from version struct of form major.minor.patch (4.1.0)
	std::string getVersionString(const Version& version);

	// gets string from version struct used for GLSL header of form {major}{minor}0 (450, 410, etc.)
	std::string getVersionStringGLSL(const Version& version);
}

