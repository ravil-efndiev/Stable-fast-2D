#include "Camera.hpp"
#include "engine/GLAPI.hpp"

namespace s2f
{
	Camera::Camera(const glm::vec2& position, f32 zoom, f32 rotation)
		: position(position), zoom(zoom), rotation(rotation) {}

	ProjViewData Camera::projview() const
	{
		auto viewport = glapi::getViewportSize();
		f32 aspect = (f32)viewport.x / (f32)viewport.y;
		return makeOrthoPojectionView(position, rotation, zoom, aspect);
	}
}
