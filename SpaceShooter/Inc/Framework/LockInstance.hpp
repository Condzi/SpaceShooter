/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Debug.hpp"

namespace con
{
	// Call in constructor if you want to make sure there is only one instance.
	template <typename T>
	void LockInstance()
	{
		if constexpr (IS_DEBUG)
		{
			static bool instanceCreated = false;
			Assert( !instanceCreated );
			instanceCreated = true;
		}
	}
}
