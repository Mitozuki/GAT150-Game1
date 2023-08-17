#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:
		/*
		Weapon(float speed, const kiko::Transform& transform) :
			Actor{ transform },
			m_speed{ speed }
		{
			lifespan = 2.0f;
		}
		*/

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollision(Actor* other);

		void Read(const json_t& value);

	private:
		float speed = 0;
	};
}