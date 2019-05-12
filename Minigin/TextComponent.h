#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"

namespace dae
{
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::string& fontPath, unsigned int fontSize);
		~TextComponent();

		void SetText(const std::string& text);

	protected:
		void Initialize() override;
		void Update() override;
	private:
		dae::Font* m_pFont;
		std::string m_Text;
		Texture2D m_Texture;
	};
}

