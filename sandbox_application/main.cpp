#include "sf2d.hpp"

using namespace s2f;

class GameLayer;
class TestLayer : public Layer
{
public:
	void start() override
	{
		Application::get()->renderInfo().clearColor = { 1.f, 0.f, 0.f, 1.f };
	}

	void onUpdate(f32 dt) override
	{
		if (Input::keyPressed(Key::Space))
			transitionTo<GameLayer>();
	}

	void onRender() override
	{
	}
};

void testSystem(const std::vector<Entity>& entities, f32 dt)
{
	for (auto& entity : entities)
	{
		if (!entity.has<Transform>() || !entity.has<Sprite>()) return;

		entity.get<Transform>()->rotation.z += 1.f * dt;
	}
}

class GameLayer : public Layer
{
public:
	void start() override
	{
		Application::get()->renderInfo().clearColor = { 0.f, 0.f, 0.f, 1.f };
		Entity sprite = mScene.newEntity();
		sprite.add<Sprite>(ASSETS_PATH / "textures" / "container.jpg");
		//sprite.get<Sprite>()->setSubTexture({ 0, 0 }, { 200, 200 });
		useCamera(mCamera);

		mScene.addSystem(testSystem);
	}

	void onUpdate(f32 dt) override
	{
		mScene.update(dt);
		if (Input::mouseButtonPressed(Mouse::Left))
			transitionTo<TestLayer>();

		if (Input::keyDown(Key::D))
			mCamera.position.x += 10.f * dt;
	}

	void onRender() override
	{
		mSceneRenderer.render();
	}

	void onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<KeyPressEvent>([this](KeyPressEvent& event) { return onKeyPress(event); });
	}

	bool onKeyPress(KeyPressEvent& event)
	{
		log::info("caugh key press event in GameLayer, key: {}, handled here", (u32)event.key);
		return S2F_EVENT_HANDLED;
	}

private:
	Camera mCamera;
};


class OverlayLayer : public Layer
{
public:
	void start() override
	{
		Entity sprite = mScene.newEntity();
		sprite.add<Sprite>(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprite.get<Transform>()->scale = { 0.3f, 0.3f, 0.3f };
		sprite.get<Transform>()->position = {-0.5f, 0.5f, 0.1f};
	}

	void onUpdate(f32 dt) override
	{
		mScene.update(dt);
		glm::vec2 mouse = Input::mousePosition();
		log::info("mouse pos = ({}, {})", mouse.x, mouse.y);
	}

	void onRender() override
	{
		mSceneRenderer.render();
	}

	void onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<KeyPressEvent>([this](KeyPressEvent& event) { return onKeyPress(event); });
	}

	bool onKeyPress(KeyPressEvent& event)
	{
		log::info("caugh key press event in OverlayLayer, key: {}, propagated further", (u32)event.key);
		return S2F_EVENT_PROPAGATED;
	}
};

int main()
{
	globals::gConfig.logMode = LogMode::Verbose;
	Application app({ { 1000, 700 }, "Sandbox" });
	app.pushLayer<GameLayer>();
	app.pushLayer<OverlayLayer>();
	app.mainLoop();
	return 0;
}
