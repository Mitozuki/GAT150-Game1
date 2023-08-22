#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
    CLASS_DEFINITION(CircleCollisionComponent)

    //class Component;

    void CircleCollisionComponent::Update(float dt)
    {
    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
    {
        float distance = m_owner->transform.position.Distance(collision->m_owner->transform.position);
        float radius = m_radius + collision->m_radius;

        if (distance <= radius) return true;

        return false;
    }

    void CircleCollisionComponent::Read(const json_t& value)
    {
        //
    }
}
