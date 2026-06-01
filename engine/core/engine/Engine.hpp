#pragma once
#include "Window.hpp"
#include "time.hpp"
#include "Renderer.hpp"
#include "inputState.hpp"
#include "events/events.hpp"

namespace s2f
{
	/*
	* @brief initialization struct for Engine class
	*/
	struct EngineInfo 
	{
		glm::vec4 clearColor{ 0.f, 0.f, 0.f, 0.f };
		RendererInfo rendererInfo{ RenderMode::Fill, 5000 };
		WindowInfo windowInfo;
	};

	/*
	* @brief Main engine class responsible for window creation,
	* OpenGL initialization, Renderer creation, time managment
	* and event dispatching
	*/
	class Engine 
	{
	public:
		/*
		* @brief Constructor of Engine
		* 
		* also sets static instance of Engine, only one engine instance can exist
		* 
		* @param info engine initialization struct
		*/
		Engine(const EngineInfo& info);
		~Engine() = default;

		/*
		* @return Engine is running and window is open state
		*/
		bool runs() const;

		/*
		* @brief Shuts down engine and closes the window
		*/
		void stop();

		/*
		* @brief Executes internal engine code at the start of a frame
		* @note should be called at the start of runtime loop
		*/
		void startFrame();

		/*
		* @brief Executes internal engine code at the end of a frame
		* 
		* should be called at the end of runtime loop
		*/
		void endFrame();

		/*
		* @brief Method to set event handling callback
		* 
		* once event gets raised inside engine event function gets called
		* 
		* can be used to define user behaviour on specific events
		* @param eventFunc event callback of type void(Event&)
		*/
		void setEventFunc(const EventFunc& eventFunc) { mEventFunc = eventFunc; }

		f32 deltaTime() const { return (f32)mTime.deltaTime; }
		f32 currentTime() const { return (f32)mTime.currentTime; }
		f32 fixedDeltaTime() const { return mTime.fixedDeltaTime; }
		Time time() const { return mTime; }
		Renderer& renderer() { return mRenderer; }

		/*
		* @brief Sets color that is used to clear the screen on every frame
		* @param clearColor background clear color
		*/
		void setClearColor(const glm::vec4& clearColor) { mClearColor = clearColor; }
		
		/*
		* @brief Static method that returns Engine instance
		* @return Engine instance pointer
		*/
		static Engine* get();

	private:
		void start();

		bool onKeyEvent(Key key, bool press);
		bool onMouseEvent(Mouse button, bool press);
		bool onMouseMove(MouseMoveEvent& event);

	private:
		Time mTime;
		Window mWindow;
		Renderer mRenderer;
		InputState mInputState{};
		EventFunc mEventFunc;
		glm::vec4 mClearColor;
	};
}
