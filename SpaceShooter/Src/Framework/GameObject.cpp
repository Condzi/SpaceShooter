/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Framework/SceneManager.hpp"

namespace con
{
	GameObject::GameObject()
	{
		static std::int16_t counter = -1;
		uniqueID = ++counter;
	}

	std::int16_t GameObject::UniqueID() const
	{
		return uniqueID;
	}

	void GameObject::Suicide()
	{
		SceneManager().ActiveScene()->KillUnique(UniqueID());
	}
}
