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

		entity.get<Transform>()->rotation += 1.f * dt;
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
		if (Input::keyPressed(Key::Space))
			transitionTo<TestLayer>();

		if (Input::keyDown(Key::D))
			mCamera.position.x += 10.f * dt;
	}

	void onRender() override
	{
		mSceneRenderer.render();
	}

private:
	Camera mCamera;
};

int main()
{
	globals::gConfig.logMode = LogMode::Verbose;
	Application app({ { 1000, 700 }, "Sandbox" });
	app.pushLayer<GameLayer>();
	app.mainLoop();
	return 0;
}
