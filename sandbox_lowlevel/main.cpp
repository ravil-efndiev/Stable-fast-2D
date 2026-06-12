#include "sf2d.hpp"

using namespace s2f;

bool onKeyPress(KeyPressEvent& event)
{
	Logger::info("key {} pressed, caught from event func", (u32)event.key);
	return S2F_EVENT_HANDLED;
}

int main()
{
	Logger::setLogMode(LogMode::Verbose);

	EngineInfo engineInfo{};
	engineInfo.windowInfo.size = { 1000, 700 };
	engineInfo.windowInfo.title = "Sandbox";

	Engine engine(engineInfo);
	Renderer& renderer = engine.renderer();
	Camera camera;

	Scene scene;
	SceneRenderer sr(scene, renderer);
	Entity sprite = scene.newEntity();
	//sprite.add<Sprite>(ASSETS_PATH / "textures" / "container.jpg");

	Entity particleTest = scene.newEntity();
	auto& emitter = *particleTest.add<ParticleEmitter>(100u, ParticleRenderPreference::Instancing);
	emitter.useAdditiveBlend = true;

	ParticlePorperties particleProps{};
	particleProps.velocityVariation = { 1.f, 3.f };
	particleProps.colorStart = { 1.f, 0.4f, 0.3f, 1.f };
	particleProps.colorEnd = { 0.3f, 0.1f, 0.1f, 0.1f };
	particleProps.lifetime = 3.f;
	particleProps.sizeStart = 0.0005f;
	particleProps.sizeEnd = 0.1f;
	particleProps.rotationChange = 1.f;

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
		emitter.emit(particleProps);

		if (Input::keyDown(Key::D))
			camera.position.x += 10.f * dt;

		renderer.setProjview(camera.projview());
		renderer.begin();
		sr.render();
		renderer.end();

		engine.endFrame();
	}

	return 0;
}
