/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <unordered_map>
#include <string>

#include "Debug.hpp"

// Forward declarations.
namespace sf
{
	class RenderWindow;
}

namespace con
{
	class ResourceStorage;
	class SceneManager;
}

namespace con::priv
{
	struct GlobalPointers final
	{
		inline static ResourceStorage* ResourceStorage = nullptr;
		inline static SceneManager* SceneManager = nullptr;
		inline static sf::RenderWindow* RenderWindow = nullptr;
		inline static float FrameDelta = 0.0f;
		inline static bool Exit = false;
		inline static std::unordered_map<std::string, std::string>* PlayerStats = nullptr;
	};

	auto Global()
	{
		if constexpr (IS_DEBUG)
		{
			Assert( GlobalPointers::ResourceStorage );
			Assert( GlobalPointers::SceneManager );
			Assert( GlobalPointers::RenderWindow );
			Assert( GlobalPointers::PlayerStats );
		}

		struct
		{
			ResourceStorage& ResourceStorage = *GlobalPointers::ResourceStorage;
			SceneManager& SceneManager = *GlobalPointers::SceneManager;
			sf::RenderWindow& RenderWindow = *GlobalPointers::RenderWindow;
			float& FrameDelta = GlobalPointers::FrameDelta;
			bool& Exit = GlobalPointers::Exit;
			std::unordered_map<std::string, std::string>& PlayerStats = *GlobalPointers::PlayerStats;
		} static refs;

		return refs;
	}
}
