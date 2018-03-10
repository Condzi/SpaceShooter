/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <unordered_map>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Framework/GameObject.hpp"
#include "Framework/ResourceStorage.hpp"

#include "Tags.hpp"
#include "HealthAttribute.hpp"
#include "Missile.hpp"
#include "DeathScene.hpp"

using namespace con;

class Player final :
	public GameObject,
	public HealthAttribute
{
public:
	std::int16_t Tag() const override
	{
		return static_cast<std::int16_t>(Tag::GameObject::PLAYER);
	}

	void OnSpawn() override
	{
		PlayerStats()["score"] = "";
		sprite.setTexture(GetResource().Texture("player"));
		sprite.setScale(GRAPHIC_SCALE, GRAPHIC_SCALE);
		sprite.setPosition(WindowSize().x / 2.0f - sprite.getGlobalBounds().width / 2.0f,
		                   WindowSize().y - sprite.getGlobalBounds().height);
		SetHealth(3);
	}

	void OnEvent(const sf::Event& ev) override
	{
		if (ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::Space)
		{
			auto missilePos = sprite.getPosition();
			missilePos += (sf::Vector2f(3.5f, -2.0f) * GRAPHIC_SCALE);
			Scene()->Spawn<Missile>().Setup(Tag(), missilePos, {0, -MAX_VELOCITY * 1.1f}, sf::Color::Magenta);
		}
	}

	void Update() override
	{
		if (IsDead())
		{
			// Play death animation here.
			SceneManager().SetActiveScene<DeathScene>();
			return;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			velocity.x -= ACCELERATION;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			velocity.x += ACCELERATION;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			velocity.y -= ACCELERATION;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			velocity.y += ACCELERATION;


		if (velocity.x < -MAX_VELOCITY)
			velocity.x = -MAX_VELOCITY;
		else if (velocity.x > MAX_VELOCITY)
			velocity.x = MAX_VELOCITY;
		if (velocity.y < -MAX_VELOCITY)
			velocity.y = -MAX_VELOCITY;
		else if (velocity.y > MAX_VELOCITY)
			velocity.y = MAX_VELOCITY;

		sprite.move(velocity * FrameDelta());
		correctIfOutOfWindow();
	}

	void Draw() override
	{
		Render(sprite);
		RenderDebugText("HP: " + std::to_string(Health()), "game", {0, WindowSize().y - 40.f}, 40);
		RenderDebugText("Score: " + std::to_string(score), "game", {100, WindowSize().y - 40.f}, 40);
	}

	auto Bounds() const
	{
		return sprite.getGlobalBounds();
	}

	void AddScore(std::int16_t val)
	{
		Assert( val > 0 );
		score += val;
		PlayerStats()["score"] = std::to_string(score);
	}

private:
	sf::Sprite sprite;
	sf::Vector2f velocity{0, 0};
	static constexpr float ACCELERATION = 10.0f;
	static constexpr float MAX_VELOCITY = 150.0f;
	std::int16_t score;

	void correctIfOutOfWindow()
	{
		auto spriteBounds = sprite.getGlobalBounds();
		auto windowBounds = sf::Rect<std::uint32_t>({0, 0}, WindowSize());
		auto spriteFinalPos = sprite.getPosition();
		auto finalVelocity = velocity;

		if (spriteBounds.left < 0)
		{
			spriteFinalPos.x = 0;
			velocity.x = 0;
		}
		else if (spriteBounds.left + spriteBounds.width > windowBounds.width)
		{
			velocity.x = 0;
			spriteFinalPos.x = windowBounds.width - spriteBounds.width;
		}

		if (spriteBounds.top < 0)
		{
			velocity.y = 0;
			spriteFinalPos.y = 0;
		}
		else if (spriteBounds.top + spriteBounds.height > windowBounds.height)
		{
			velocity.y = 0;
			spriteFinalPos.y = windowBounds.height - spriteBounds.height;
		}

		sprite.setPosition(spriteFinalPos);
	}
};
