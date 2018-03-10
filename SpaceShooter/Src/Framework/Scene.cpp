/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Framework/Scene.hpp"

namespace con
{
	void Scene::OnEvent(const sf::Event& ev)
	{
		for (std::size_t i = 0; i < gameObjects.size(); ++i)
		{
			auto& go = gameObjects[i];
			if (go)
				go->OnEvent(ev);
		}
	}

	void Scene::Update()
	{
		for (std::size_t i = 0; i < gameObjects.size(); ++i)
		{
			auto& go = gameObjects[i];
			if (go)
				go->Update();
		}
	}

	void Scene::Draw()
	{
		for (std::size_t i = 0; i < gameObjects.size(); ++i)
		{
			auto& go = gameObjects[i];
			if (go)
				go->Draw();
		}
	}

	bool Scene::Kill(std::int16_t gameObjectTag)
	{
		auto result = std::find_if(gameObjects.begin(), gameObjects.end(),
		                           [&](auto& go) { return go->Tag() == gameObjectTag; });

		if (result != gameObjects.end())
		{
			(*result)->OnKill();
			gameObjects.erase(result);
			return true;
		}

		Print("Can't kill GameObject with tag ", gameObjectTag, '.');
		return false;
	}

	bool Scene::KillUnique(std::int16_t uniqueID)
	{
		auto result = std::find_if(gameObjects.begin(), gameObjects.end(),
		                           [&](auto& go) { return go->UniqueID() == uniqueID; });

		if (result != gameObjects.end())
		{
			(*result)->OnKill();
			gameObjects.erase(result);
			Print("Killed GameObject of id ", uniqueID, '.');
			return true;
		}

		Print("Can't kill GameObject of id ", uniqueID, '.');
		return false;
	}

	std::vector<GameObject*> Scene::GameObjectsOfTag(std::int16_t tag)
	{
		std::vector<GameObject*> toReturn;

		for (auto& go : gameObjects)
			if (go->Tag() == tag)
				toReturn.emplace_back(go.get());

		return toReturn;
	}
}
