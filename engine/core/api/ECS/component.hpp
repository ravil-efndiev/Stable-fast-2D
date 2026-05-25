#pragma once
#include "include.hpp"

namespace s2f
{
	inline ComponentTypeId sComponentTypeCounter{ 0 };

	template <class T>
	ComponentTypeId getComponentType()
	{
		static ComponentTypeId currentId = sComponentTypeCounter++;
		return currentId;
	}
}
