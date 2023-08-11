#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
    void CircleCollsionComponent::Update(float dt)
    {
    }

    bool CircleCollsionComponent::CheckCollision(CollisionComponent* collision)
    {
        float distance = m_owner->m_transform.position.Distance(collision->m_owner->m_transform.position);
        float radius = m_radius + collision->m_radius;

        if (distance <= radius) return true;

        return false;
    }
}
