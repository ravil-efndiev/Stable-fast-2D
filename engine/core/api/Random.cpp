#include "Random.hpp"

#define ASSERT_INITIALIZED S2F_ASSERT(sGenerator, "Random was not initialized when calling its methods, use Random::init()")

namespace s2f
{
	std::mt19937* Random::sGenerator;

	void Random::init(std::mt19937* generator)
	{
		sGenerator = generator;
	}

	i32 Random::nextInt(i32 max) { return intRange(0, max); }

	u32 Random::nextUint(u32 max) { return uintRange(0, max); }
	
	f64 Random::nextFloat64(f64 max) { return float64Range(0.0, max); }
	
	f32 Random::nextFloat32(f32 max) { return float32Range(0.f, max); }

	i32 Random::intRange(i32 min, i32 max)
	{
		ASSERT_INITIALIZED;
		validateRange(min, max);
		std::uniform_int_distribution<i32> dist(min, max);
		return dist(*sGenerator);
	}

	u32 Random::uintRange(u32 min, u32 max)
	{
		ASSERT_INITIALIZED;
		validateRange(min, max);
		std::uniform_int_distribution<u32> dist(min, max);
		return dist(*sGenerator);
	}

	f64 Random::float64Range(f64 min, f64 max)
	{
		ASSERT_INITIALIZED;
		validateRange(min, max);
		std::uniform_real_distribution<f64> dist(min, max);
		return dist(*sGenerator);
	}

	f32 Random::float32Range(f32 min, f32 max)
	{
		ASSERT_INITIALIZED;
		validateRange(min, max);
		std::uniform_real_distribution<f32> dist(min, max);
		return dist(*sGenerator);
	}

	bool Random::probability(f64 chance)
	{
		return float64Range(0.0, 1.0) <= chance;
	}

	bool Random::probability(f32 chance)
	{
		return float32Range(0.f, 1.f) <= chance;
	}

	template<Numeric T>
	void Random::validateRange(T& min, T& max)
	{
		if (min > max)
		{
			std::swap(min, max);
			Logger::warn("Invalid range passed to one of methods of Random (min > max), min and max swapped");
		}
	}

	template void Random::validateRange<i32>(i32&, i32&);
	template void Random::validateRange<u32>(u32&, u32&);
	template void Random::validateRange<f32>(f32&, f32&);
	template void Random::validateRange<f64>(f64&, f64&);
}
