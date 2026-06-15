#pragma once
#include "include.hpp"

namespace s2f
{
	/*
	* @brief Represents a rectangle in 2D space with top-left coordintate start
	* @tparam T numeric type used to define position and size values
	*/
	template <Numeric T>
	struct Rect
	{	
		glm::tvec2<T> position;
		glm::tvec2<T> size;

		T left() const { return position.x; }
		T right() const { return position.x + size.x; }
		T top() const { return position.y; }
		T botttom() const { return position.y + size.y; }

		T width() const { return size.width; }
		T height() const { return size.height; }
	};

	using RectF = Rect<f32>;
	using RectI = Rect<i32>;
	using RectU = Rect<u32>;

	template <Numeric T>
    inline bool intersect(const Rect<T>& a, const Rect<T>& b)
	{
		return
			a.left() <= b.right() &&
			a.top() <= b.botttom() &&
			a.right() >= b.left() &&
			a.botttom() >= b.top()
	}
}
