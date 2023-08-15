#include "SpriteComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	CLASS_DEFINITION(SpriteComponent)

	void SpriteComponent::Update(float df)
	{
	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform);
	}
}
