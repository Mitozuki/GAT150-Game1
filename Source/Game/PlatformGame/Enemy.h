#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other);
		void OnCollisionExit(Actor* other);

	private:
		float m_speed = 0;
		float m_jump = 0;
		int groundCount = 0;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}