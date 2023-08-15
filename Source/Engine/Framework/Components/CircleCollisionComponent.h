#pragma once
#include "CollisionComponent.h"

namespace kiko
{
	class CircleCollsionComponent : public CollisionComponent
	{
	public:
		CLASS_DECLARATION(CircleCollsionComponent)

		// Inherited via CollisionComponent
		virtual void Update(float dt) override;

		virtual bool CheckCollision(CollisionComponent* collision) override;

	public:

	};
}