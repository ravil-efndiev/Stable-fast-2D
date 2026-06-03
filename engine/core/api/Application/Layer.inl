#pragma once
#include "Application.hpp"

namespace s2f
{
    template <std::derived_from<Layer> ToLayerT, class... Args>
    void Layer::transitionTo(Args&& ...args)
    {
        Application::get()->template enqueueLayerTransition<ToLayerT>(this, std::forward<Args>(args)...);
    }
}
