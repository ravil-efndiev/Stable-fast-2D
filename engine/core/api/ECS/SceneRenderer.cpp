#include "SceneRenderer.hpp"
#include "DefaultComponents/sprite.hpp"
#include "DefaultComponents/transform.hpp"

namespace s2f
{
	static void drawSprites(const std::vector<Entity>& entities, Renderer& renderer)
	{
		for (const auto& entity : entities)
		{
			if (!entity.has<Transform>() || !entity.has<Sprite>()) continue;

			auto* transform = entity.get<Transform>();
			auto* sprite = entity.get<Sprite>();

			if (sprite->texture->valid())
			{
				if (sprite->subTexture.valid())
					renderer.drawQuad(transform->matrix(), sprite->texture.get(), sprite->subTexture, sprite->color);
				else
					renderer.drawQuad(transform->matrix(), sprite->texture.get(), sprite->color);
			}
			else
				renderer.drawQuad(transform->matrix(), sprite->color);
		}
	}

	SceneRenderer::SceneRenderer(Scene& scene, Renderer& renderer)
		: mScene(scene), mRenderer(renderer)
	{
		mRenderLayers.reserve(10);
		mRenderLayers.emplace_back(drawSprites, 0);
	}

	void SceneRenderer::render()
	{
		auto entities = mScene.entities();
		for (auto& layer : mRenderLayers)
		{
			layer.drawFunc(entities, mRenderer);
		}
	}

	void SceneRenderer::pushRenderLayer(const RenderLayer& layer)
	{
		mRenderLayers.push_back(layer);
		sortLayers();
	}

	void SceneRenderer::pushRenderLayer(SceneRendererDrawFunc drawFunc, u32 order)
	{
		mRenderLayers.emplace_back(drawFunc, order);
		sortLayers();
	}

	void SceneRenderer::sortLayers()
	{
		std::sort(mRenderLayers.begin(), mRenderLayers.end(),
			[](const RenderLayer& layer1, const RenderLayer& layer2)
			{
				return layer1.order > layer2.order;
			}
		);
	}
}
