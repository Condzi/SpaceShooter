/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include "Global.hpp"

namespace con
{
	class Scene;

	class GlobalAccesable
	{
	public:
		GlobalAccesable() = default;
		GlobalAccesable(GlobalAccesable&&) = default;
		GlobalAccesable(const GlobalAccesable&) = default;
		GlobalAccesable& operator=(const GlobalAccesable&) = default;
		virtual ~GlobalAccesable() = default;

	protected:
		ResourceStorage& GetResource() const;
		void Render(const sf::Drawable& drawable) const;
		void RenderDebugText(const std::string& text, const std::string& font, const sf::Vector2f& position,
		                     std::size_t size);
		float FrameDelta() const;
		float FramesPerSecond() const;
		SceneManager& SceneManager() const;
		Scene* Scene() const;
		sf::Vector2u WindowSize() const;
		void Exit() const;
		bool IsOffScreen(const sf::FloatRect& rect) const;
		std::unordered_map<std::string, std::string>& PlayerStats() const;
	};
}
