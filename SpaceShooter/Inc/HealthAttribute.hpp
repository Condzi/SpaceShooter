/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <cinttypes>

#include "Framework/Debug.hpp"

using namespace con;

class HealthAttribute
{
public:
	virtual ~HealthAttribute() = default;

	void AddDamage(std::int32_t val)
	{
		if constexpr (IS_DEBUG)
			Assert( val > 0 );

		health -= val;
		if (health < 0) health = 0;
	}

	void AddHealth(std::int32_t val)
	{
		if constexpr (IS_DEBUG)
			Assert( val > 0 );

		health += val;
	}

	void SetHealth(std::int32_t val)
	{
		if constexpr (IS_DEBUG)
			Assert( val >= 0 );

		health = val;
	}

	bool IsDead() const
	{
		return health == 0;
	}

	std::int32_t Health() const
	{
		return health;
	}

private:
	std::int32_t health = 1;
};
