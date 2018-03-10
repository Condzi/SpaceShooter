/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "SceneManager.hpp"
#include "ResourceStorage.hpp"
#include "Global.hpp"

namespace con
{
	class Game final
	{
	public:
		Game();

		template <typename TScene>
		void StartWithScene()
		{
			sceneManager.SetActiveScene<TScene>();
		}

		void Run();

	private:
		ResourceStorage resourceStorage;
		SceneManager sceneManager;
		sf::RenderWindow renderWindow;
		std::unordered_map<std::string, std::string> playerStats;

		// Named 'Print' instead 'print' just to follow convention.
		template <typename ...TArgs>
		void Print(TArgs&& ...args) const
		{
			static_assert( sizeof...( TArgs ) > 0, "No arguments provided." );
			DebugPrint("Game: ", std::forward<TArgs>(args)...);
		}

		void initGlobalPointers();
		void eventPoll();
	};
}
