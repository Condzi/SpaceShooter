/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Framework/GameObject.hpp"
#include "Framework/ResourceStorage.hpp"

#include "Tags.hpp"
#include "Config.hpp"

using namespace con;

class Missile final :
	public GameObject
{
public:
	std::int16_t Tag() const override
	{
		return static_cast<std::int16_t>( Tag::GameObject::MISSILE );
	}

	void Setup( std::int16_t tag, const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& color )
	{
		ownerTag = tag;
		velocity = vel;
		sprite.setColor( color );
		sprite.setPosition( pos );
	}

	void SetOwnerTag( std::int16_t tag )
	{
		ownerTag = tag;
	}

	std::int16_t OwnerTag() const
	{
		return ownerTag;
	}

	sf::Vector2f Velocity() const
	{
		return velocity;
	}

	auto Bounds() const
	{
		return sprite.getGlobalBounds();
	}

	void OnSpawn() override
	{
		sprite.setTexture( GetResource().Texture( "missile" ) );
		sprite.setScale( GRAPHIC_SCALE, GRAPHIC_SCALE );
	}

	void Update() override
	{
		if ( IsOffScreen( sprite.getGlobalBounds() ) )
			return Suicide();

		sprite.move( velocity * FrameDelta() );
	}

	void Draw() override
	{
		Render( sprite );
	}

private:
	std::int16_t ownerTag = 0;
	sf::Vector2f velocity{ 0, 0 };
	sf::Sprite sprite;
};
