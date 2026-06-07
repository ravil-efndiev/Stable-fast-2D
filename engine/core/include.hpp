#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <optional>
#include <memory>
#include <functional>
#include <stack>
#include <unordered_map>
#include <format>
#include <concepts>

#ifdef WIN32
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "keys.hpp"
#include "Logger.hpp"

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

	using EntityId = u32;
	using ComponentTypeId = u32;
	using SystemId = u32;

	const std::filesystem::path ASSETS_PATH{ "assets" };
	const std::filesystem::path SHADER_PATH{ ASSETS_PATH / "shaders" };

	enum class RenderMode : u8
	{
		Fill, Wireframe
	};
}

#ifdef S2F_DEBUG

	#define S2F_ASSERT(cond, s) \
		if (!(cond)) { \
			s2f::Logger::verror(s); \
			std::abort(); \
		} \

#else

	#define S2F_ASSERT(cond, s)

#endif
