#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

	public:
		Enemy(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{
			m_fireRate = 2.0f;
			m_fireTimer = m_fireRate;
		}

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollision(Actor* other) override;
	private:
		float m_speed = 0;
		float m_turnRate = 0;

		float m_fireRate = 0;
		float m_fireTimer = 0;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};

}