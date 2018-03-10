/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/Graphics/Image.hpp>

#include "Framework/LockInstance.hpp"
#include "Framework/ResourceStorage.hpp"
#include "Framework/DefaultFont.hpp"

namespace con
{
	ResourceStorage::ResourceStorage()
	{
		LockInstance<ResourceStorage>();

		initFallbackTexture();
		initFallbackFont();
	}

	const sf::Texture& ResourceStorage::Texture(const std::string& name) const
	{
		if (name == "default")
			return fallbackTexture;

		if (auto txtIt = textures.find(name); txtIt != textures.end())
			return txtIt->second;
		Print("Can't find texture \"", name, "\".");
		return fallbackTexture;
	}

	bool ResourceStorage::LoadTexture(const std::string& path, const std::string& name)
	{
		if (auto txtIt = textures.find(name); txtIt != textures.end())
		{
			Print("Texture \"", name, "\" already loaded.");
			return false;
		}

		sf::Texture texture;
		if (!texture.loadFromFile(path))
		{
			Print("Texture \"", name, "\" failed to load from file: \"", path, "\".");
			return false;
		}

		// Slow?
		textures[name] = std::move(texture);
		Print("Add texture \"", name, "\".");
		return true;
	}

	bool ResourceStorage::UnloadTexture(const std::string& name)
	{
		if (auto txtIt = textures.find(name); txtIt != textures.end())
		{
			textures.erase(txtIt);
			return true;
		}

		Print("Can't remove texture \"", name, "\".");
		return false;
	}

	const sf::Font& ResourceStorage::Font(const std::string& name) const
	{
		if (name == "default")
			return fallbackFont;

		if (auto fontIt = fonts.find(name); fontIt != fonts.end())
			return fontIt->second;
		Print("Can't find font \"", name, "\".");
		return fallbackFont;
	}

	bool ResourceStorage::LoadFont(const std::string& path, const std::string& name)
	{
		if (auto fontIt = fonts.find(name); fontIt != fonts.end())
		{
			Print("Font \"", name, "\" already loaded.");
			return false;
		}

		sf::Font font;
		if (!font.loadFromFile(path))
		{
			Print("Font \"", name, "\" failed to load from file: \"", path, "\".");
			return false;
		}

		// Slow?
		fonts[name] = std::move(font);
		Print("Add font \"", name, "\".");
		return true;
	}

	bool ResourceStorage::UnloadFont(const std::string& name)
	{
		if (auto fontIt = fonts.find(name); fontIt != fonts.end())
		{
			fonts.erase(fontIt);
			return true;
		}

		Print("Can't remove font \"", name, "\".");
		return false;
	}

	void ResourceStorage::initFallbackTexture()
	{
		sf::Image errorImg;
		errorImg.create(64, 64, sf::Color::Magenta);
		fallbackTexture.loadFromImage(errorImg);
	}

	void ResourceStorage::initFallbackFont()
	{
		fallbackFont = priv::DefaultFont();
	}
}
