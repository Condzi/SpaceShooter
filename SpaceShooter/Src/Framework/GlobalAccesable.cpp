/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Framework/SceneManager.hpp"
#include "Framework/GlobalAccesable.hpp"
#include "Framework/ResourceStorage.hpp"

namespace con
{
ResourceStorage& GlobalAccesable::GetResource() const
{
	return priv::Global().ResourceStorage;
}

void GlobalAccesable::Render( const sf::Drawable& drawable ) const
{
	priv::Global().RenderWindow.draw( drawable );
}

void GlobalAccesable::RenderDebugText( const std::string& text, const std::string& font, const sf::Vector2f& position,
									   std::size_t size )
{
	sf::Text toRender;
	toRender.setString( text );
	toRender.setFont( GetResource().Font( font ) );
	toRender.setPosition( position );
	toRender.setCharacterSize( size );

	Render( toRender );
}

float GlobalAccesable::FrameDelta() const
{
	return priv::Global().FrameDelta;
}

float GlobalAccesable::FramesPerSecond() const
{
	return 1 / FrameDelta();
}

SceneManager& GlobalAccesable::SceneManager() const
{
	return priv::Global().SceneManager;
}

Scene* GlobalAccesable::Scene() const
{
	return priv::Global().SceneManager.ActiveScene();
}

sf::Vector2u GlobalAccesable::WindowSize() const
{
	return priv::Global().RenderWindow.getSize();
}

void GlobalAccesable::Exit() const
{
	priv::Global().Exit = true;
}

bool GlobalAccesable::IsOffScreen( const sf::FloatRect& rect ) const
{
	return !rect.intersects( sf::FloatRect( 0, 0, WindowSize().x, WindowSize().y ) );
}

std::unordered_map<std::string, std::string>& GlobalAccesable::PlayerStats() const
{
	return priv::Global().PlayerStats;
}
}
