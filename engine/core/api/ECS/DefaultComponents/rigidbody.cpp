#include "rigidbody.hpp"

namespace s2f
{
    Rigidbody::Rigidbody(f32 mass, f32 linearDamping)
        : linearDamping(linearDamping) 
    {
        setMass(mass);
    }

    void Rigidbody::setMass(f32 mass)
    {
        if (mass > 0.f)
        {
            this->mass = mass;
            massInverse = 1.f / mass;
        }
        else
        {
            this->mass = 0.f;
            massInverse = 0.f;
        }
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
