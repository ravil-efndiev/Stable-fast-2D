#include "sf2d.hpp"

int main()
{
	s2f::Engine engine({ {1000, 700}, "Sandbox" });
	s2f::Renderer& renderer = engine.renderer();

	s2f::Texture texture;
	texture.create(s2f::ASSETS_PATH / "textures" / "container.jpg");

	while (engine.runs()) 
	{
		engine.startFrame();
		renderer.drawQuad({ {0.3, 0.3, 0}, {0, 0, 0}, {1, 1, 1} }, &texture, { 1 ,0, 0, 1 });
		renderer.drawQuad({ {0, 0, 0}, {0, 0, 0}, {1, 1, 1} }, { 1 ,1, 1, 1 });
		//renderer.drawQuad({ {0.3, 0.3, 0}, {0, 0, 0}, {1, 1, 1} }, { 1 ,0, 0, 1 });
		engine.endFrame();

		auto stats = renderer.frameStatistics();
		S2F_INFO("quad count: " << stats.quadCount);
		S2F_INFO("draw calls: " << stats.drawCalls);
		renderer.resetStatistics();
	}

	return 0;
}
