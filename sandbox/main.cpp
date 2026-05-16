#include "sf2d.hpp"

int main()
{
	s2f::Engine engine({ {1000, 700}, "Sandbox" });
	s2f::Renderer& renderer = engine.renderer();

	s2f::Texture texture;
	texture.create(s2f::ASSETS_PATH / "textures" / "container.jpg");

	s2f::Camera camera;

	while (engine.runs()) 
	{
		engine.startFrame();
		renderer.setProjview(camera.projview());
		renderer.drawQuad({ {0.3, 0.3, 0}, {0, 0, 0}, {1, 1, 1} }, &texture, { 1 ,0, 0, 1 });
		renderer.drawQuad({ {0, 0, 0}, {0, 0, 0}, {1, 1, 1} }, { 1 ,1, 1, 1 });
		//renderer.drawQuad({ {0.3, 0.3, 0}, {0, 0, 0}, {1, 1, 1} }, { 1 ,0, 0, 1 });
		engine.endFrame();
	}

	return 0;
}
