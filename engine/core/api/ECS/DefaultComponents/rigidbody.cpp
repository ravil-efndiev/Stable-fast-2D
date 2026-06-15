#include "rigidbody.hpp"

namespace s2f
{
    Rigidbody::Rigidbody(f32 mass)
        : mass(mass), massInverse(1.f / mass) {}

    void Rigidbody::setMass(f32 mass)
    {
        this->mass = mass;
        massInverse = 1.f / this->mass;
    }
}
