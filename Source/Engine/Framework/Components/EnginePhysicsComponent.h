#pragma once
#include "PhysicsComponent.h"

namespace kiko
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:

		// Inherited via PhysicsComponent
		void Update(float dt) override;
		void ApplyForce(const vec2& force) override;

	};
}