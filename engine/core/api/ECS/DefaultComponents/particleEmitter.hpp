#include "engine/Texture.hpp"

namespace s2f
{
	enum class ParticleRenderPreference
	{
		Batching = 0, Instancing
	};

	struct ParticlePorperties
	{
		glm::vec4 colorStart{ 1.f };
		glm::vec4 colorEnd{ 1.f };

		glm::vec2 offset{ 0.f };
		glm::vec2 velocity{ 0.f };
		glm::vec2 velocityVariation{ 0.f };

		f32 sizeStart{ 1.f };
		f32 sizeEnd{ 1.f };
		f32 sizeVariation{ 0.f };
		f32 lifetime{ 1.f };
		f32 rotationChange{ 0.f };
		bool randomStartRotation{ false };
	};

	struct Particle
	{
		glm::vec4 colorStart{ 1.f };
		glm::vec4 colorEnd{ 1.f };
		
		glm::vec2 position{ 0.f };
		glm::vec2 velocity{ 0.f };
		
		f32 sizeStart{ 1.f };
		f32 sizeEnd{ 1.f };
		f32 rotation{ 0.f };
		f32 rotationChange{ 0.f };
		f32 lifetime{ 0.f };
		f32 lifetimeRemaining{ 0.f };
		bool active{ false };
	};

	struct ParticleEmitter
	{
		std::vector<Particle> particles;
		std::shared_ptr<Texture> texture;
		ParticleRenderPreference renderPreference{};
		bool useAdditiveBlend{ false };

		ParticleEmitter(u32 particleCount, ParticleRenderPreference preference);
		ParticleEmitter(u32 particleCount, const std::filesystem::path& texturePath, ParticleRenderPreference preference);
		void emit(const ParticlePorperties& props);

	private:
		u64 mIndex{ 0 };
	};
}
