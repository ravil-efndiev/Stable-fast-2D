#include "sf2d.hpp"

using namespace s2f;

int main()
{
	globals::gConfig.logMode = LogMode::Verbose;
	Engine engine({ {1000, 700}, "Sandbox" });
	Renderer& renderer = engine.renderer();
	Camera camera;

	Scene scene;
	SceneRenderer sr(scene, renderer);
	Entity sprite = scene.newEntity();
	sprite.add<Sprite>(ASSETS_PATH / "textures" / "container.jpg");

	while (engine.runs()) 
	{
		engine.startFrame();

		f32 dt = engine.deltaTime();
		scene.update(dt);

		if (Input::keyDown(Key::D))
			camera.position.x += 10.f * dt;

		if (Input::keyPressed(Key::Space))
			S2F_INFO("Space key was pressed!");

		if (Input::keyReleased(Key::Space))
			S2F_INFO("Space key was released!");

		renderer.setProjview(camera.projview());
		sr.render();

		engine.endFrame();
	}

	return 0;
}
