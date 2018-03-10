/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <random>
#include <chrono>

namespace con
{
	namespace priv
	{
		static std::mt19937
		rndEngine(static_cast<std::uint32_t>(std::chrono::steady_clock::now().time_since_epoch().count()));
	}

	template <typename T, typename Y>
	T Random(const T& min, const Y& max)
	{
		static_assert( std::is_integral_v<T> || std::is_floating_point_v<T> );
		T maxCasted = static_cast<T>(max);

		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<T> dist(min, maxCasted);
			return dist(priv::rndEngine);
		}
		else if constexpr (std::is_floating_point_v<T>)
		{
			std::uniform_real_distribution<T> dist(min, maxCasted);
			return dist(priv::rndEngine);
		}
	}
}
