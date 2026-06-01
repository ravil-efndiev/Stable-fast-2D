#pragma once
#include "include.hpp"

namespace s2f
{
	/*
	* @brief Represents a rectangle in 2D space with top-left coordintate start
	* @tparam T numeric type used to define position and size values
	*/
	template <class T>
	requires std::integral<T> || std::floating_point<T>
	struct Rect
	{	
		glm::tvec2<T> position;
		glm::tvec2<T> size;

		T left() const { return position.x; }
		T top() const { return position.y; }
		T width() const { return size.width; }
		T height() const { return size.height; }
	};

	using RectF = Rect<f32>;
	using RectI = Rect<i32>;
	using RectU = Rect<u32>;
}
