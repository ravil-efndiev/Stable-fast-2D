#include "particleEmitter.hpp"
#include "api/Random.hpp"

namespace s2f
{
	ParticleEmitter::ParticleEmitter(u32 particleCount, ParticleRenderPreference preference)
		: renderPreference(preference)
	{
		particles.resize(particleCount);
	}

	ParticleEmitter::ParticleEmitter(u32 particleCount, const std::filesystem::path& texturePath, ParticleRenderPreference preference)
		: renderPreference(preference)
	{
		particles.resize(particleCount);
		texture = std::make_shared<Texture>(texturePath);
	}

	void ParticleEmitter::emit(const ParticlePorperties& props)
	{
		if (mIndex >= particles.size())
			mIndex = 0;

		Particle& particle = particles[mIndex];

		particle.active = true;
		particle.position = props.offset;

		particle.velocity = props.velocity;
		particle.velocity.x += props.velocityVariation.x * Random::float32Range(-0.5f, 0.5f);
		particle.velocity.y += props.velocityVariation.y * Random::float32Range(-0.5f, 0.5f);

		particle.colorStart = props.colorStart;
		particle.colorEnd = props.colorEnd;

		if (props.randomStartRotation)
			particle.rotation = Random::nextFloat32(1.f) * glm::two_pi<f32>();

		particle.rotationChange = props.rotationChange;
		particle.lifetime = props.lifetime;
		particle.lifetimeRemaining = props.lifetime;
		particle.sizeStart = props.sizeStart + props.sizeVariation * Random::float32Range(-0.5f, 0.5f);
		particle.sizeEnd = props.sizeEnd;

		mIndex++;
	}
}
