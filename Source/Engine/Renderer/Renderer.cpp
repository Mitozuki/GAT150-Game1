#include"Renderer.h"
#include "Texture.h"
#include "SDL2-2.28.0/include/SDL_ttf.h"
#include "SDL2-2.28.0/include/SDL_image.h"

namespace kiko
{
	Renderer g_renderer;

	bool Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();

		return true;
	}
	void Renderer::Shutdown()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		TTF_Quit();
		IMG_Quit();
	}
	void Renderer::CreateWindow(const std::string& title, int width, int height)
	{
		m_width = width;
		m_height = height;

		m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}
	void Renderer::BeginFrame()
	{
		SDL_RenderClear(m_renderer);
	}
	void Renderer::EndFrame()
	{
		SDL_RenderPresent(m_renderer);
	}
	void Renderer::SetColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A)
	{
		SDL_SetRenderDrawColor(m_renderer, R, G, B, A);
	}
	void Renderer::DrawLine(int x1, int y1, int x2, int y2)
	{
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
	}
	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}
	void Renderer::DrawPoint(int x, int y)
	{
		SDL_RenderDrawPoint(m_renderer, x, y);
	}
	void Renderer::DrawPoint(float x, float y)
	{
		SDL_RenderDrawPointF(m_renderer, x, y);
	}
	void Renderer::DrawTexture(Texture* texture, const Transform& transform)
	{
		mat3 mx = transform.GetMatrix();

		vec2 position = mx.GetTranslate();
		vec2 size = texture->GetSize() * mx.GetScale();

		SDL_Rect dest;
		dest.x = position.x - (size.x * 0.5);
		dest.y = position.y - (size.y * 0.5);
		dest.w = size.x;
		dest.h = size.y;

		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
		SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, RadiansToDeg(mx.GetRotation()), nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}
	void Renderer::DrawTexture(Texture* texture, float x, float y, float angle)
	{
		vec2 size = texture->GetSize();
			SDL_Rect dest;
			dest.x = x - (size.x * 0.5);
			dest.y = y - (size.y* 0.5);
			dest.w = size.x;
			dest.h = size.y;

			// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
			SDL_RenderCopyEx(m_renderer, texture->m_texture, NULL, NULL, angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
	}
}
