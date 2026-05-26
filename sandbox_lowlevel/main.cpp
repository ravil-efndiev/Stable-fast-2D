#include "sf2d.hpp"

using namespace s2f;

bool onKeyPress(KeyPressEvent& event)
{
	log::info("key {} pressed, caught from event func", (u32)event.key);
	return S2F_EVENT_HANDLED;
}

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

	engine.setEventFunc([](Event& event) 
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<KeyPressEvent>(onKeyPress);
	});

	while (engine.runs()) 
	{
		engine.startFrame();

		f32 dt = engine.deltaTime();
		scene.update(dt);

		if (Input::keyDown(Key::D))
			camera.position.x += 10.f * dt;

		renderer.setProjview(camera.projview());
		sr.render();

		engine.endFrame();
	}

	return 0;
}
