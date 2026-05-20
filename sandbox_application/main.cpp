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

	void update(f32 dt) override
	{
		if (Input::keyPressed(Key::Space))
			transitionTo<GameLayer>();
	}

	void render() override
	{
	}
};

class GameLayer : public Layer
{
public:
	void start() override
	{
		Application::get()->renderInfo().clearColor = { 0.f, 0.f, 0.f, 1.f };
		Entity sprite = mScene.newEntity();
		sprite.add<Transform>();
		sprite.add<Sprite>(ASSETS_PATH / "textures" / "container.jpg");
		sprite.get<Sprite>()->setSubTexture({ 0, 0 }, { 200, 200 });
	}

	void update(f32 dt) override
	{
		if (Input::keyPressed(Key::Space))
			transitionTo<TestLayer>();
	}

	void render() override
	{
		mSceneRenderer.render();
	}
};

int main()
{
	globals::gConfig.logMode = LogMode::Verbose;
	Application app({ { 1000, 700 }, "Sandbox" });
	app.pushLayer<GameLayer>();
	app.mainLoop();
	return 0;
}
