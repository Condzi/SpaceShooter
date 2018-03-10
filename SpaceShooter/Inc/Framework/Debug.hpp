/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <iostream>
#include <string>
#include <type_traits>
#include <intrin.h>

namespace con
{
#ifdef NDEBUG
constexpr bool IS_DEBUG = false;
#else
constexpr bool IS_DEBUG = true;
#endif // NDEBUG

template <typename ...TArgs>
void DebugPrint( TArgs&& ...args );

namespace priv
{
inline void _assert( bool expr, const char* exprStr, const char* file, std::uint32_t line );
}

#define DebugBreak() if constexpr ( con::IS_DEBUG ) __debugbreak()
#define Assert( x ) priv::_assert( !!(x), #x, __FILE__, __LINE__  )


template <typename ...TArgs>
void DebugPrint( TArgs&& ...args )
{
	( std::cout << ... << args ) << '\n';
}

namespace priv
{
inline void _assert( bool expr, const char* exprStr, const char* file, std::uint32_t line )
{
	if ( expr ) return;

	DebugPrint( "====================" );
	DebugPrint( "Assertion failed!" );
	DebugPrint( "Expression: ", exprStr );
	DebugPrint( "At: ", file, ":", line );
	DebugBreak();
}
}
}
