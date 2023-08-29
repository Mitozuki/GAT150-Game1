#include "Player.h"
#include "Framework/Framework.h"

#include "Renderer/Texture.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Emitter.h"
#include "Renderer/Model.h"

namespace kiko
{
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimRenderComponent>();

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		bool onGround = (groundCount > 0);

		// movement
		float dir = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		kiko::vec2 forward = kiko::vec2{ 1 , 0 };

		m_physicsComponent->ApplyForce(forward * m_speed * dir * ((onGround) ? 1 : 0.25f));

		// jump
		if (onGround && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::vec2 up = kiko::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(up * m_jump);
		}
		
		// animation
		vec2 velocity = m_physicsComponent->m_velocity;
		if (std::fabs(velocity.x) > 0.2f)
		{
			if (dir != 0) m_spriteAnimComponent->fliph = (dir < 0);
			m_spriteAnimComponent->SetSequence("run");
		}
		else {
			m_spriteAnimComponent->SetSequence("idle");
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		/*
		if (other->tag == "Enemy")
		{
			destroyed = true;
			kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}
		*/

		if (other->tag == "Ground") groundCount++;
	}
	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, m_speed);
		READ_DATA(value, m_jump);
	}

}