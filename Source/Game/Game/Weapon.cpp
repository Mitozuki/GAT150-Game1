#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	bool WeaponComponent::Initialize()
	{
		auto collisionComponent = m_owner->GetComponent<kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = m_owner->GetComponent<kiko::RenderComponent>();
			if (renderComponent)
			{
				float scale = m_owner->transform.scale;
				collisionComponent->m_radius = m_owner->GetComponent<kiko::RenderComponent>()->GetRadius() * scale;
			}
		}

		return true;
	}

	void WeaponComponent::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 foward = kiko::vec2{ 0, -1 }.Rotate(m_owner->transform.rotation);
		m_owner->transform.position += foward * speed * kiko::g_time.GetDeltaTime();
		m_owner->transform.position.x = kiko::Wrap(m_owner->transform.position.x, (float)kiko::g_renderer.GetWidth());
		m_owner->transform.position.y = kiko::Wrap(m_owner->transform.position.y, (float)kiko::g_renderer.GetHeight());
	}

	void WeaponComponent::OnCollision(Actor* other)
	{
		if (other->tag != m_owner->tag)
		{
			m_owner->destroyed = true;
		}
	}
	void WeaponComponent::Read(const json_t& value)
	{
		READ_DATA(value, speed);
	}
}
