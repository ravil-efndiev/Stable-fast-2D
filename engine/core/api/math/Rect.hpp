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

		T left() const    { return position.x; }
		T right() const   { return position.x + size.x; }
		T top() const     { return position.y; }
		T botttom() const { return position.y + size.y; }

		T width() const { return size.width; }
		T height() const { return size.height; }
	};

	using RectF = Rect<f32>;
	using RectD = Rect<f64>;
	using RectI = Rect<i32>;
	using RectU = Rect<u32>;

	/*
	* @brief Represents a rectangle in 2D space with center coordintate start
	* @tparam T floating point type used to define position and size values
	*/
	template <std::floating_point T>
	struct RectCenter
	{	
		glm::tvec2<T> position;
		glm::tvec2<T> size;

		T left() const    { return position.x - size.x * T(0.5); }
		T right() const   { return position.x + size.x * T(0.5); }
		T top() const     { return position.y - size.y * T(0.5); }
		T bottom() const  { return position.y + size.y * T(0.5); }

		T width() const { return size.width; }
		T height() const { return size.height; }
	};

	using RectCenterF = RectCenter<f32>;
	using RectCenterD = RectCenter<f64>;

	template <class RectT>
	concept RectType = 
	requires(const RectT& r)
	{
		r.left();
		r.right();
		r.top();
		r.bottom();
	};

	template <RectType RectT>
    inline bool intersect(const RectT& a, const RectT& b)
	{
		return
			a.left() <= b.right() &&
			a.top() <= b.botttom() &&
			a.right() >= b.left() &&
			a.botttom() >= b.top();
	}
}
