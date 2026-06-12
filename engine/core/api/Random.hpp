#pragma once
#include "include.hpp"

namespace s2f
{
    /*
    * @brief Global static class responsible for managing random number distributions and chances
    */
	class Random
	{
	public:
        /*
        * @brief Sets up internal rnd generator pointer, used by engine internally
        * @param generator pointer to a generator
        */
		static void init(std::mt19937* generator);

        /*
        * @return 32-bit random integer in range [0, max]
        * @param max maximum value of range, inclusive
        */
        static i32 nextInt(i32 max);

        /*
        * @return 32-bit random unsigned integer in range [0, max]
        * @param max maximum value of range, inclusive
        */
        static u32 nextUint(u32 max);

        /*
        * @return 64-bit random float in range [0, max)
        * @param max maximum value of range, exclusive
        */
        static f64 nextFloat64(f64 max);

        /*
        * @return 32-bit random float in range [0, max)
        * @param max maximum value of range, exclusive
        */
        static f32 nextFloat32(f32 max);

        /*
        * @return 32-bit random integer in range [min, max]
        * @param min minimum value of range
        * @param max maximum value of range, inclusive
        */
        static i32 intRange(i32 min, i32 max);

        /*
        * @return 32-bit random unsigned integer in range [min, max]
        * @param min minimum value of range
        * @param max maximum value of range, inclusive
        */
        static u32 uintRange(u32 min, u32 max);

        /*
        * @return 64-bit random float in range [min, max)
        * @param min minimum value of range
        * @param max maximum value of range, exclusive
        */
        static f64 float64Range(f64 min, f64 max);

        /*
        * @return 32-bit random float in range [min, max)
        * @param min minimum value of range
        * @param max maximum value of range, exclusive
        */
        static f32 float32Range(f32 min, f32 max);

        /*
        * @brief Generates a number between 0 and 1 and checks if chance succeeds
        * 
        * For percents use pct() funciton
        * 
        * @param chance chance value in range [0, 1]
        * @return wether chance succeeds
        */
        static bool probability(f64 chance);

        /*
        * @brief Generates a number between 0 and 1 and checks if chance succeeds
        *
        * For percents use pct() funciton
        *
        * @param chance chance value in range [0, 1]
        * @return wether chance succeeds
        */
        static bool probability(f32 chance);

    private:
        template <Numeric T>
        static void validateRange(T& min, T& max);

	private:
		static std::mt19937* sGenerator;
	};

    // Converts passed percentage value in range [0, 100] into probability range [0, 1]
    inline f32 pct(f32 percent) { return percent / 100.f; }

    // Converts passed percentage value in range [0, 100] into probability range [0, 1]
    inline f64 pct(f64 percent) { return percent / 100.0; }
}
