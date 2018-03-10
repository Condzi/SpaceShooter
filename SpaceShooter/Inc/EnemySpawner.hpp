/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Enemy.hpp"
#include "Framework/UtilityFunctions.hpp"

using namespace con;


// TODO: Change sf::Time to float
class EnemySpawner :
	public GameObject
{
public:
	std::int16_t Tag() const override
	{
		return static_cast<std::int16_t>(Tag::GameObject::ENEMY_SPAWNER);
	}

	void Setup(const sf::Time& minFireTime, const sf::Time& maxFireTime, const sf::Time& spawnIntervalBeg,
	           const sf::Time& spawnIntervalEn)
	{
		Assert( minFireTime < maxFireTime );
		Assert( spawnIntervalBeg < spawnIntervalEn );

		minFireRate = minFireTime.asSeconds();
		maxFireRate = maxFireTime.asSeconds();
		spawnIntervalBegin = spawnIntervalBeg.asSeconds();
		spawnIntervalEnd = spawnIntervalEn.asSeconds();
		spawnTimeTarget = spawnIntervalBegin;
	}

	void Update() override
	{
		spawnTimeCounter += FrameDelta();

		if (spawnTimeCounter >= spawnTimeTarget)
		{
			spawnTimeCounter = 0;
			spawnTimeTarget = Random(spawnIntervalBegin, spawnIntervalEnd);
			spawn();
		}
	}

private:
	static constexpr float MIN_VELOCITY = 75.0f;
	static constexpr float MAX_VELOCITY = 100.0f;
	float minFireRate, maxFireRate;
	float spawnIntervalBegin, spawnIntervalEnd;
	float spawnTimeTarget; // randomized value between intervals
	float spawnTimeCounter;

	void spawn()
	{
		sf::Vector2f pos(Random(0, WindowSize().x - 8 * GRAPHIC_SCALE), -16 * GRAPHIC_SCALE);
		sf::Vector2f vel(Random(-MIN_VELOCITY, MAX_VELOCITY), Random(MIN_VELOCITY, MAX_VELOCITY));
		auto rate = sf::seconds(Random(minFireRate, maxFireRate));

		Scene()->Spawn<Enemy>().Setup(pos, vel, rate);
	}
};
