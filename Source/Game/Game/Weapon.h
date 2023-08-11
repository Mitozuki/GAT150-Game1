#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"

class Weapon : public kiko::Actor
{
public:
	Weapon(float speed, const kiko::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
};