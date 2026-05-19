#include "sf2d.hpp"

using namespace s2f;

class GameLayer : public Layer
{
public:
	GameLayer(Application& app) : Layer(app) {}

	void start() override
	{
		Entity sprite = mScene.newEntity();
		sprite.add<Transform>();
		sprite.add<Sprite>(ASSETS_PATH / "textures" / "container.jpg", glm::vec4(1.f));
	}

	void update(f32 dt) override
	{

	}

	void render() override
	{
		mSceneRenderer.render();
	}
};

int main()
{
	Application app({ { 1000, 700 }, "Sandbox" });
	app.pushLayer<GameLayer>();
	app.mainLoop();
	return 0;
}
