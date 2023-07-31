#pragma once
#include "Renderer.h"
#include "Font.h"
#include "Core/Color.h"
#include <string>
#include <memory>
namespace kiko
{
	class Text
	{
	public:
		Text(kiko::Font* font) : m_font{ font } { }
		~Text();
		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, int x, int y);
		friend class Font;
	private:
		kiko::Font* m_font;
		struct SDL_Texture* m_texture = nullptr;
	};
}