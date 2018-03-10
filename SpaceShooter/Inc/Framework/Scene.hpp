/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>
#include <vector>

#include <SFML/Window/Event.hpp>

#include "GameObject.hpp"

namespace con
{
	// Don't load resources in constructor! 
	class Scene :
		public GlobalAccesable
	{
	public:
		virtual ~Scene() = default;
		virtual std::int16_t Tag() const = 0;

		virtual void OnStart()
		{
		}

		virtual void OnStop()
		{
		}

		// Must call them in overrided methods!
		virtual void OnEvent(const sf::Event& ev);
		virtual void Update();
		virtual void Draw();

		template <typename TGameObject>
		TGameObject& Spawn()
		{
			static_assert( std::is_base_of_v<GameObject, TGameObject> );
			auto& spawnedObject = dynamic_cast<TGameObject&>(*gameObjects.emplace_back(std::make_unique<TGameObject>()));

			spawnedObject.OnSpawn();
			return spawnedObject;
		}

		bool Kill(std::int16_t gameObjectTag);
		bool KillUnique(std::int16_t uniqueID);
		std::vector<GameObject*> GameObjectsOfTag(std::int16_t tag);

	protected:
		template <typename ...TArgs>
		void Print(TArgs&& ...args) const
		{
			static_assert( sizeof...( TArgs ) > 0, "No arguments provided." );
			DebugPrint("Scene[", Tag(), "]: ", std::forward<TArgs>(args)...);
		}

	private:
		std::vector<std::unique_ptr<GameObject>> gameObjects;
	};
}
