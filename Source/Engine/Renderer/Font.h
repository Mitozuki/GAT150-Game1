#pragma once
#include "Framework/Resource/Resource.h"
#include <string>
struct _TTF_Font;
namespace kiko
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();
		bool Load(const std::string& filename, int fontSize);

		friend class Text;
		virtual bool Create(std::string filename, ...) override;

	private:
		_TTF_Font* m_ttfFont = nullptr;

		// Inherited via Resource
	};
}