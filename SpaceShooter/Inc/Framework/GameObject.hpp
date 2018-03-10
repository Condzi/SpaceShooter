/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "GlobalAccesable.hpp"

namespace con
{
class GameObject :
	public GlobalAccesable
{
public:
	GameObject();
	virtual ~GameObject() = default;

	virtual std::int16_t Tag() const = 0;
	std::int16_t UniqueID() const;

	void Suicide();

	virtual void OnSpawn() {}
	virtual void OnKill() {}
	virtual void OnEvent( const sf::Event& ev ) {}
	virtual void Update() {}
	virtual void Draw() {}

protected:
	template <typename ...TArgs>
	void Print( TArgs&& ...args ) const
	{
		static_assert( sizeof...( TArgs ) > 0, "No arguments provided" );
		DebugPrint( "GameObject[", UniqueID(), " | ", Tag(), "]: ", std::forward<TArgs>( args )... );
	}

private:
	std::int16_t uniqueID;

};
}