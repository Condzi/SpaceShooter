/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace con
{
	class ResourceStorage final
	{
	public:
		ResourceStorage();

		const sf::Texture& Texture(const std::string& name) const;
		bool LoadTexture(const std::string& path, const std::string& name);
		bool UnloadTexture(const std::string& name);

		const sf::Font& Font(const std::string& name) const;
		bool LoadFont(const std::string& path, const std::string& name);
		bool UnloadFont(const std::string& name);


	private:
		std::unordered_map<std::string, sf::Texture> textures;
		std::unordered_map<std::string, sf::Font> fonts;
		sf::Texture fallbackTexture;
		sf::Font fallbackFont;

		template <typename ...TArgs>
		void Print(TArgs&& ...args) const
		{
			static_assert( sizeof...( TArgs ) > 0, "No arguments provided." );
			DebugPrint("Resource Storage: ", std::forward<TArgs>(args)...);
		}

		void initFallbackTexture();
		void initFallbackFont();
	};
}
