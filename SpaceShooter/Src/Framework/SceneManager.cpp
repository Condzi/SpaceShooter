/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/Window/Event.hpp>

#include "Framework/SceneManager.hpp"

namespace con
{
	SceneManager::SceneManager()
	{
		LockInstance<SceneManager>();
	}

	std::optional<std::int16_t> SceneManager::ActiveSceneTag() const
	{
		if (!activeScene)
			return {};
		return activeScene->Tag();
	}

	Scene* SceneManager::ActiveScene() const
	{
		if (!activeScene)
			Print("Returning active scene, but is nullptr.");

		return activeScene.get();
	}

	void SceneManager::OnEvent(const sf::Event& ev)
	{
		if (activeScene)
			activeScene->OnEvent(ev);
	}

	void SceneManager::Update()
	{
		tryToSwitchScene();

		if (activeScene)
			activeScene->Update();
	}

	void SceneManager::Draw()
	{
		if (activeScene)
			activeScene->Draw();
	}

	void SceneManager::tryToSwitchScene()
	{
		if (pendingScene)
		{
			if (activeScene)
				activeScene->OnStop();
			activeScene = std::move(pendingScene);
			activeScene->OnStart();
			pendingScene.reset();

			Print("Switch scene to ", activeScene->Tag(), '.');
		}
	}
}
