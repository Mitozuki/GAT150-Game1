#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"

namespace kiko
{
	class SpriteComponent : public RenderComponent
	{
	public:
		void Update(float df) override;
		void Draw(class Renderer& renderer) override;
	};
}