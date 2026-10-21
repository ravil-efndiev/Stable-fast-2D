#include "SceneRenderer.hpp"
#include "DefaultComponents/sprite.hpp"
#include "DefaultComponents/transform.hpp"
#include "DefaultComponents/particleEmitter.hpp"
#include "UI/components.hpp"
#include "entityQuery.hpp"

namespace s2f
{
	static void drawSprites(const std::vector<Entity>& entities, Renderer& renderer)
	{
		for (auto&& [transform, sprite] : queryComponents<Transform, Sprite>(entities))
		{
			if (sprite.texture && sprite.texture->valid())
			{
				if (sprite.subTexture.valid())
					renderer.drawQuad(transform.matrix(), sprite.texture.get(), sprite.subTexture, sprite.color);
				else
					renderer.drawQuad(transform.matrix(), sprite.texture.get(), sprite.color);
			}
			else
				renderer.drawQuad(transform.matrix(), sprite.color);
		}
	}

	static void drawParticlesBatched(const Transform& transform, const ParticleEmitter& emitter, Renderer& renderer)
	{
		for (const auto& particle : emitter.particles)
		{
			f32 life = particle.lifetimeRemaining / particle.lifetime;
			f32 size = glm::mix(particle.sizeStart, particle.sizeEnd, life);

			glm::mat4 tf = transform.matrix() * makeTransform(
				glm::vec3(particle.position, 0.f),
				glm::vec3(0.f, 0.f, particle.rotation),
				glm::vec2(size, size)
			);

			glm::vec4 color = glm::mix(particle.colorStart, particle.colorEnd, life);

			if (emitter.texture && emitter.texture->valid())
				renderer.drawQuad(tf, emitter.texture.get(), color);
			else
				renderer.drawQuad(tf, color);
		}
	}
	
	static void drawParticlesInstanced(const Transform& transform, const ParticleEmitter& emitter, Renderer& renderer)
	{
		std::vector<glm::mat4> tfs;
		std::vector<glm::vec4> colors;
		tfs.reserve(emitter.particles.size());
		colors.reserve(emitter.particles.size());

		for (const auto& particle : emitter.particles)
		{
			if (!particle.active)
				continue;

			f32 life = particle.lifetimeRemaining / particle.lifetime;
			f32 size = glm::mix(particle.sizeStart, particle.sizeEnd, life);
			tfs.push_back(
				transform.matrix() * makeTransform(
					glm::vec3(particle.position, 0.f),
					glm::vec3(0.f, 0.f, particle.rotation),
					glm::vec2(size, size)
				)
			);

			glm::vec4 color = glm::mix(particle.colorStart, particle.colorEnd, life);
			colors.push_back(color);
		}

		if (emitter.texture && emitter.texture->valid())
			renderer.submitQuads(tfs, colors, emitter.texture.get());
		else
			renderer.submitQuads(tfs, colors);
	}

	static void drawParticles(const Transform& transform, const ParticleEmitter& emitter, Renderer& renderer)
	{
		if (emitter.renderPreference == ParticleRenderPreference::Batching)
		{
			drawParticlesBatched(transform, emitter, renderer);
		}
		else if (emitter.renderPreference == ParticleRenderPreference::Instancing)
		{
			drawParticlesInstanced(transform, emitter, renderer);
		}
	}

	static void drawParticleEmitters(const std::vector<Entity>& entities, Renderer& renderer)
	{
		auto queried = queryComponents<Transform, ParticleEmitter>(entities);

		glapi::setDepthFuncLequal();
		glapi::toggleAdditiveBlend(true);
		for (auto&& [transform, emitter] : queried)
		{
			if (!emitter.useAdditiveBlend)
				continue;

			drawParticles(transform, emitter, renderer);
		}

		renderer.flushBatchAndReset();

		glapi::toggleAdditiveBlend(false);

		for (auto&& [transform, emitter] : queried)
		{
			if (emitter.useAdditiveBlend)
				continue;

			drawParticles(transform, emitter, renderer);
		}

		renderer.flushBatchAndReset();
		glapi::setDepthFuncLess();
	}

	static void drawText(const std::vector<Entity>& entities, Renderer& _, TextRenderer& textRenderer, ui::StyleLibrary& styleLibrary)
	{
		for (auto&& [transform, text] : queryComponents<Transform, ui::Text>(entities))
		{
			if (auto* style = std::get_if<ui::Style>(&text.style))
			{
				textRenderer.drawString(text.text, transform.matrix(), style->color, style->fontName);
			}
			else if (auto* styleName = std::get_if<std::string>(&text.style))
			{
				if (auto* foundStyle = styleLibrary.getStyle(*styleName))
					textRenderer.drawString(text.text, transform.matrix(), foundStyle->color, foundStyle->fontName);
			}
		}
	}

	SceneRenderer::SceneRenderer(Scene& scene, Renderer& renderer)
		: mScene(scene), mRenderer(renderer)
	{
		mRenderLayers.reserve(10);
		mUIRenderLayers.reserve(10);
		mRenderLayers.emplace_back(drawParticleEmitters, 0);
		mRenderLayers.emplace_back(drawSprites, 1);
		mUIRenderLayers.emplace_back(drawText, 0);
	}

	void SceneRenderer::render()
	{
		auto entities = mScene.entities();
		for (auto& layer : mRenderLayers)
		{
			layer.drawFunc(entities, mRenderer);
		}

		if (!mTextRenderer || !mStyleLibrary)
			return;

		for (auto& layer : mUIRenderLayers)
		{
			layer.drawFunc(entities, mRenderer, *mTextRenderer, *mStyleLibrary);
		}
	}

	void SceneRenderer::pushRenderLayer(const RenderLayer& layer)
	{
		mRenderLayers.push_back(layer);
		sortLayers();
	}

	void SceneRenderer::pushRenderLayer(const SceneRendererDrawFunc& drawFunc, u32 order)
	{
		mRenderLayers.emplace_back(drawFunc, order);
		sortLayers();
	}

	void SceneRenderer::pushUIRenderLayer(const UIRenderLayer& layer)
	{
		mUIRenderLayers.push_back(layer);
		sortLayers();
	}

	void SceneRenderer::pushUIRenderLayer(const SceneRendererUIDrawFunc& drawFunc, u32 order)
	{
		mUIRenderLayers.emplace_back(drawFunc, order);
		sortLayers();
	}

	void SceneRenderer::useUI(TextRenderer& textRenderer, ui::StyleLibrary& styleLibrary)
	{
		mTextRenderer = &textRenderer;
		mStyleLibrary = &styleLibrary;
	}

	void SceneRenderer::sortLayers()
	{
		auto compare = [](const auto& a, const auto& b)
		{
			return a.order > b.order;
		};

		std::sort(mRenderLayers.begin(), mRenderLayers.end(), compare);
		std::sort(mUIRenderLayers.begin(), mUIRenderLayers.end(), compare);
	}
}
