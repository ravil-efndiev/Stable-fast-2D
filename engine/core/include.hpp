#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <optional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "config.hpp"
#include "keys.hpp"

#define S2F_DEBUG

namespace s2f 
{
	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;
	using i8 = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;
	using f32 = float;
	using f64 = double;

	constexpr auto COL_RED = "\033[31m";
	constexpr auto COL_GREEN = "\033[32m";
	constexpr auto COL_YELLOW = "\033[33m";
	constexpr auto COL_WHITE = "\033[37m";

	const std::filesystem::path ASSETS_PATH{ "assets" };
	const std::filesystem::path SHADER_PATH{ ASSETS_PATH / "shaders" };

	inline GlobalConfig gConfig{};
}

#define S2F_INFO(s) std::cout << s2f::COL_GREEN << "[Info] " << s2f::COL_WHITE << s << "\n"
#define S2F_WARN(s) std::cout << s2f::COL_YELLOW << "[Warn] " << s2f::COL_WHITE << s << "\n"
#define S2F_ERROR(s) std::cerr << s2f::COL_RED << "[Error] " << s2f::COL_WHITE << s << std::endl

#define S2F_INFO_VERBOSE(s) \
	if (s2f::gConfig.logMode == s2f::LogMode::Verbose) S2F_INFO(s); 

#ifdef S2F_DEBUG

#define S2F_ASSERT(cond, s) \
	if (!(cond)) { \
		S2F_ERROR(s); \
		std::abort(); \
	} \

#else

#define S2F_ASSERT(cond, s)

#endif
