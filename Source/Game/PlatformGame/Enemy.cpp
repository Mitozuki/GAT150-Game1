#include "Enemy.h"
#include "Player.h"
#include "Framework/Framework.h"

#include "Renderer/Texture.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Emitter.h"
#include "Renderer/Model.h"

namespace kiko
{
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * m_speed);
		}
	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		/*
		if (other->tag == "Player")
		{
			destroyed = true;
		}
		*/

		if (other->tag == "Ground") groundCount++;
	}
	void Enemy::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, m_speed);
		READ_DATA(value, m_jump);
	}

}