#include "Application.hpp"

namespace s2f
{
    static Application* sInstance{ nullptr };

    Application* Application::get()
    {
        S2F_ASSERT(sInstance, "Application::get() Application was not initialized");
        return sInstance;
    }

	Application::Application(const EngineInfo& engineInfo)
		: mEngine(engineInfo)
    {
        S2F_ASSERT(!sInstance, "Application instance can only be created once");
        sInstance = this;

        mEngine.setEventFunc([this](Event& event)
        {
            for (const auto& layer : std::views::reverse(mLayers))
                layer->onEvent(event);
        });
    }

    void Application::mainLoop()
    {
        for (const auto& layer : mLayers)
            layer->start();

        while (mEngine.runs())
        {
            mEngine.startFrame();

            for (const auto& layer : mLayers)
                layer->update(mEngine.deltaTime());

            for (const auto& layer : mLayers)
                layer->render();

            mEngine.endFrame();
            executeLayerTransitions();
        }
    }

    void Application::executeLayerTransitions()
    {
        if (mLayerTransitions.empty()) return;
        for (auto& transition : mLayerTransitions)
        {
            for (auto& layer : mLayers)
            {
                if (transition.from == layer.get())
                {
                    transition.to->start();
                    layer = std::move(transition.to);
                    break;
                }
            }
        }
       
        mLayerTransitions.clear();
    }

    void Application::stop()
    {
        mEngine.stop();
    }
}
