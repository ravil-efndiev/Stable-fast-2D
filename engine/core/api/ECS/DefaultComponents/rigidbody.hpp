#pragma once
#include "include.hpp"

namespace s2f
{
    struct Rigidbody
    {
        glm::vec2 forces{};
        glm::vec2 velocity{};
        f32 mass{ 1.f };
        f32 massInverse{ 1.f };
        f32 linearDamping{ 0.f };
        bool resolveCollisions{ false };

        Rigidbody(f32 mass, f32 linearDamping = 0.f);
        void setMass(f32 mass);

        void addForceX(f32 force);
        void addForceY(f32 force);
        void addForce(const glm::vec2& forces);
    };
}
