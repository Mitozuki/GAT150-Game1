#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Renderer/Renderer.h"
#include "Renderer/Emitter.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Enemy)

	bool Enemy::Initialize()
	{

		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<kiko::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = GetComponent<kiko::RenderComponent>()->GetRadius() * scale;
			}
		}

		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		bool shoot = false;
		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::Vector2 direction = player->transform.position - transform.position;

			float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());

			//transform.rotation += turnAngle * 5 * dt;
			m_physicsComponent->ApplyTorque(turnAngle);
			float angle = kiko::vec2::Angle(forward, direction.Normalized());
			if (std::fabs(turnAngle) < kiko::DegreesToRad(30.0f))
			{
				shoot = true;
			}
		}

		m_physicsComponent->ApplyForce(forward * m_speed);

		//transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

		m_fireTimer -= dt;
	}

	void Enemy::OnCollision(Actor* other)
	{
		//dynamic_cast<Player*>(other);

		if (other->tag == "Player")
		{
			kiko::EventManager::Instance().DispatchEvent("AddPoints", 100);
			//m_game->AddScore(100);
			destroyed = true;

			kiko::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = kiko::pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;

			data.color = kiko::Color{ 1, 1, 0, 1 };

			kiko::Transform transform{ this->transform.position, 0, 1 };
			auto emitter = std::make_unique<kiko::Emitter>(transform, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, m_speed);
		READ_DATA(value, m_turnRate);
		READ_DATA(value, m_fireRate);
	}
}

