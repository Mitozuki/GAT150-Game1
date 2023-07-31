#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Renderer/Renderer.h"
#include "Renderer/Emitter.h"
#include "Framework/Scene.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	bool shoot = false;
	kiko::vec2 foward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;

		float turnAngle = kiko::vec2::SignedAngle(foward, direction.Normalized());

		m_transform.rotation += turnAngle * 5 * dt;

		float angle = kiko::vec2::Angle(foward, direction.Normalized());
		if (std::fabs(turnAngle) < kiko::DegreesToRad(30.0f))
		{
			shoot = true;
		}
	}

	m_transform.position += foward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	m_fireTimer -= dt;
	if (m_fireTimer <= 0 && shoot && m_type == Base)
	{
		kiko::Transform transform{ m_transform.position, m_transform.rotation, m_transform.scale };
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
		m_scene->Add(std::move(weapon));

		m_fireTimer = m_fireRate;
	}

	if (m_fireTimer <= 0 && shoot && m_type == Special)
	{

		kiko::Transform transform{ m_transform.position, m_transform.rotation, m_transform.scale };
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
		m_scene->Add(std::move(weapon));

		kiko::Transform transform1{ m_transform.position, m_transform.rotation + kiko::DegreesToRad(10.0f), m_transform.scale };
		std::unique_ptr<Weapon> weapon2 = std::make_unique<Weapon>(400.0f, transform1, m_model);
		m_scene->Add(std::move(weapon2));
		
		kiko::Transform transform2{ m_transform.position, m_transform.rotation - kiko::DegreesToRad(10.0f), m_transform.scale };
		std::unique_ptr<Weapon> weapon3 = std::make_unique<Weapon>(400.0f, transform2, m_model);
		m_scene->Add(std::move(weapon3));

		m_fireTimer = m_fireRate;
	}
}

void Enemy::OnCollision(Actor* other)
{
	//dynamic_cast<Player*>(other);

	if (other->m_tag == "Player")
	{
		m_game->AddScore(100);
		m_destroyed = true;

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
		kiko::Transform transform{ m_transform.position, 0, 1 };
		auto emitter = std::make_unique<kiko::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
}

