#include "sf2d.hpp"

int main()
{
	s2f::gConfig.logMode = s2f::LogMode::Verbose;
	s2f::Engine engine({ {1000, 700}, "Sandbox" });
	s2f::Renderer& renderer = engine.renderer();

	s2f::Texture texture;
	texture.create(s2f::ASSETS_PATH / "textures" / "container.jpg");

	s2f::Camera camera;

	while (engine.runs()) 
	{
		engine.startFrame();

		if (s2f::Input::keyDown(s2f::Key::D))
			camera.position.x += 10.f * engine.deltaTime();

		if (s2f::Input::keyPressed(s2f::Key::Space))
			S2F_INFO("Space key was pressed!");

		if (s2f::Input::keyReleased(s2f::Key::Space))
			S2F_INFO("Space key was released!");

		renderer.setProjview(camera.projview());
		renderer.drawQuad({ {0.3, 0.3, 0}, {0, 0, 0}, {1, 1, 1} }, &texture, { 1 ,0, 0, 1 });
		renderer.drawQuad({ {0, 0, 0}, {0, 0, 0}, {1, 1, 1} }, { 1 ,1, 1, 1 });
		//renderer.drawQuad({ {0.3, 0.3, 0}, {0, 0, 0}, {1, 1, 1} }, { 1 ,0, 0, 1 });
		engine.endFrame();
	}

	return 0;
}
