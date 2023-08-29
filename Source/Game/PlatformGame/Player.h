#pragma once
#include "Framework/Actor.h"

namespace kiko
{
	class Player : public Actor
	{
	public:
		CLASS_DECLARATION(Player)

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other);
		void OnCollisionExit(Actor* other);

	private:
		float m_speed = 0;
		float m_jump = 0;
		int groundCount = 0;

		class PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimRenderComponent* m_spriteAnimComponent = nullptr;
	};
}