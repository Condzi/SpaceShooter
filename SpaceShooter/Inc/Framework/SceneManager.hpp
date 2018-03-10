/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>
#include <optional>

#include "Scene.hpp"
#include "LockInstance.hpp"

namespace con
{
	class SceneManager final
	{
		using SceneUPtr = std::unique_ptr<Scene>;
	public:
		SceneManager();

		template <typename TScene>
		void SetActiveScene()
		{
			static_assert( std::is_base_of_v<Scene, TScene> );

			auto newPendingScene = std::make_unique<TScene>();
			Print("Request switch to scene ", newPendingScene->Tag(), '.');

			if constexpr (IS_DEBUG)
				if (pendingScene)
				{
					if (pendingScene->Tag() == newPendingScene->Tag())
						Print("Overweiring pending scene that has the same tag.");
					else
						Print("Overwriting pending scene.");
				}

			pendingScene = std::move(newPendingScene);
		}

		std::optional<std::int16_t> ActiveSceneTag() const;
		Scene* ActiveScene() const;

		void OnEvent(const sf::Event& ev);
		void Update();
		void Draw();

	private:
		SceneUPtr activeScene;
		SceneUPtr pendingScene;

		// Named 'Print' instead 'print' just to follow convention.
		template <typename ...TArgs>
		void Print(TArgs&& ...args) const
		{
			static_assert( sizeof...( TArgs ) > 0, "No arguments provided." );
			DebugPrint("Scene Manager: ", std::forward<TArgs>(args)...);
		}

		void tryToSwitchScene();
	};
}
