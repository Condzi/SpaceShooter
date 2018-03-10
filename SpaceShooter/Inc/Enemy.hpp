/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include "Framework/GameObject.hpp"
#include "Framework/ResourceStorage.hpp"
#include "Framework/Scene.hpp"

#include "Tags.hpp"
#include "HealthAttribute.hpp"
#include "Missile.hpp"

using namespace con;

class Enemy final :
	public GameObject,
	public HealthAttribute
{
public:
	std::int16_t Tag() const override
	{
		return static_cast<std::int16_t>(Tag::GameObject::ENEMY);
	}

	void Setup(const sf::Vector2f& startPos, const sf::Vector2f& vel, const sf::Time& fireRate)
	{
		sprite.setPosition(startPos);
		velocity = vel;
		fireInterval = fireRate;
	}

	void OnSpawn() override
	{
		sprite.setTexture(GetResource().Texture("player"));
		sprite.setColor(sf::Color::Green);
		sprite.setScale(GRAPHIC_SCALE, GRAPHIC_SCALE);
		sprite.rotate(180.0f);
		// Make oring at top-left corner (inverted when rotated)
		sprite.setOrigin(8, 16);
	}

	void Update() override
	{
		eleapsedTime += sf::seconds(FrameDelta());

		if (eleapsedTime >= fireInterval)
		{
			eleapsedTime = sf::seconds(0);
			fire();
		}

		sprite.move(velocity * FrameDelta());
		correctIfOutOfWindow();
		// TODO: remove player health or something
		if (IsOffScreen(sprite.getGlobalBounds()) || IsDead())
			Suicide();
	}

	void Draw() override
	{
		Render(sprite);
	}

	auto Bounds() const
	{
		return sprite.getGlobalBounds();
	}

private:
	sf::Sprite sprite;
	sf::Vector2f velocity{0, 0};
	sf::Time eleapsedTime;
	sf::Time fireInterval = sf::seconds(0.9f);
	static constexpr float MISSILE_VELOCITY = 150.0f;

	void fire()
	{
		auto missilePos = sprite.getPosition();
		missilePos += (sf::Vector2f(3.5f, 16.0f) * GRAPHIC_SCALE);
		Scene()->Spawn<Missile>().Setup(Tag(), missilePos, {0, MISSILE_VELOCITY}, sf::Color::Yellow);
	}

	void correctIfOutOfWindow()
	{
		auto spriteBounds = sprite.getGlobalBounds();
		auto windowBounds = sf::Rect<std::uint32_t>({0, 0}, WindowSize());
		auto spriteFinalPos = sprite.getPosition();
		auto finalVelocity = velocity;

		if (spriteBounds.left < 0)
		{
			spriteFinalPos.x = 0;
			velocity.x = -velocity.x;
		}
		else if (spriteBounds.left + spriteBounds.width > windowBounds.width)
		{
			velocity.x = -velocity.x;
			spriteFinalPos.x = windowBounds.width - spriteBounds.width;
		}

		if (spriteBounds.top + spriteBounds.height > windowBounds.height)
		{
			velocity.y *= 1.1f;
			velocity.x *= 0.5f;
		}

		sprite.setPosition(spriteFinalPos);
	}
};
