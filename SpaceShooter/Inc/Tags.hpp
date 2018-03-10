/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

namespace Tag
{
	enum struct GameObject
	{
		PLAYER,
		// TODO:
		MISSILE,
		ENEMY,

		MISSILE_HIT_RESOLVER,
		ENEMY_SPAWNER
	};

	enum struct Scene
	{
		PLAY,
		DEATH
	};
}
