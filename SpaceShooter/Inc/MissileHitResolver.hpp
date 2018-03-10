/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Framework/Scene.hpp"

#include "Enemy.hpp"
#include "Player.hpp"

using namespace con;

class MissileHitResolver :
	public GameObject
{
public:
	std::int16_t Tag() const override
	{
		return static_cast<std::int16_t>(Tag::GameObject::MISSILE_HIT_RESOLVER);
	}

	void Update() override
	{
		auto enemyTag = static_cast<std::int16_t>(Tag::GameObject::ENEMY);
		auto playerTag = static_cast<std::int16_t>(Tag::GameObject::PLAYER);
		auto missilesVec = Scene()->GameObjectsOfTag(static_cast<std::int16_t>(Tag::GameObject::MISSILE));
		auto playerVec = Scene()->GameObjectsOfTag(playerTag);
		auto enemiesVec = Scene()->GameObjectsOfTag(enemyTag);

		if (missilesVec.empty())
			return;

		Player* player = playerVec.empty() ? nullptr : dynamic_cast<Player*>(playerVec.back());

		for (auto m : missilesVec)
		{
			Missile* missile = dynamic_cast<Missile*>(m);
			Assert( missile );

			if (missile->OwnerTag() == enemyTag && player != nullptr)
			{
				if (missile->Bounds().intersects(player->Bounds()))
				{
					player->AddDamage(1);
					missile->Suicide();
				}
			}
			else if (missile->OwnerTag() == playerTag && !enemiesVec.empty())
			{
				for (auto e : enemiesVec)
				{
					Enemy* enemy = dynamic_cast<Enemy*>(e);
					Assert( enemy );

					if (missile->Bounds().intersects(enemy->Bounds()))
					{
						missile->Suicide();
						enemy->AddDamage(1);
						player->AddScore(10);
					}
				}
			}
		}
	}
};
