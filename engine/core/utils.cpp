#include "utils.hpp"

namespace s2f
{
	std::string getTextFromFile(const std::filesystem::path& path)
	{
		std::ifstream file(path.string());
		S2F_ASSERT(file.is_open(), "Failed to open file: " + path.string());

		std::stringstream fileData;
		fileData << file.rdbuf();
		return fileData.str();
	}
}
