#include "rigidbody.hpp"

namespace s2f
{
    Rigidbody::Rigidbody(f32 mass, f32 linearDamping)
        : mass(mass), massInverse(1.f / mass), linearDamping(linearDamping) {}

    void Rigidbody::setMass(f32 mass)
    {
        this->mass = mass;
        massInverse = 1.f / this->mass;
    }

    void Rigidbody::addForceX(f32 force)
    {
        forces.x += force;
    }

    void Rigidbody::addForceY(f32 force)
    {
        forces.y += force;
    }

    void Rigidbody::addForce(const glm::vec2& forces)
    {
        this->forces += forces;
    }
}
