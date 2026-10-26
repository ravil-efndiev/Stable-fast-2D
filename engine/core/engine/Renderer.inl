#include "Renderer.hpp"

namespace s2f
{
    template <class VertexType, class VertexFactory, class... Spans>
    std::vector<VertexType> Renderer::makeInstanceVector(VertexFactory factory, std::span<glm::mat4> transforms, Spans... attributes)
    {
        auto count = transforms.size();

        if (!((attributes.size() == count) && ...))
        {
            Logger::error("makeInstanceVector() collection sizes must match");
            return {};
        }

        std::vector<VertexType> instances;
        instances.reserve(count);

        for (size_t i{}; i < count; ++i)
        {
            instances.emplace_back(
                factory(transforms[i], attributes[i]...)
            );
        }

        return instances;
    }
}