#pragma once
#include "CollisionComponent.h"

namespace kiko
{
	class CircleCollsionComponent : public CollisionComponent
	{
	public:
		// Inherited via CollisionComponent
		virtual void Update(float dt) override;

		virtual bool CheckCollision(CollisionComponent* collision) override;

	public:

	};
}