#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"
#include "Framework/Factory.h"

namespace kiko
{
	class SpriteComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(SpriteComponent)

		void Update(float df) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_texture->GetSize().Length() * 0.5f; }

	public:
		res_t<Texture> m_texture;
	};
}