/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Framework/Scene.hpp"

#include "Tags.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "MissileHitResolver.hpp"
#include "EnemySpawner.hpp"

using namespace con;

class PlayScene final :
	public Scene
{
public:
	std::int16_t Tag() const override
	{
		return static_cast<std::int16_t>(Tag::Scene::PLAY);
	}

	void OnEvent(const sf::Event& ev) override
	{
		Scene::OnEvent(ev);

		if (ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::Escape)
			Exit();
	}

	void OnStart() override
	{
		GetResource().LoadTexture("Res/Ship.png", "player");
		GetResource().LoadTexture("Res/Missile.png", "missile");
		GetResource().LoadTexture("Res/BG.png", "background");
		GetResource().LoadFont("Res/munro_small.ttf", "game");


		Spawn<Player>();
		Spawn<MissileHitResolver>();
		Spawn<EnemySpawner>().Setup(sf::seconds(1.0f), sf::seconds(5.0f), sf::seconds(1.5f), sf::seconds(3.0f));

		background.setTexture(GetResource().Texture("background"));
		background.setScale(GRAPHIC_SCALE, GRAPHIC_SCALE);
	}

	void Draw() override
	{
		Render(background);
		Scene::Draw();
		RenderDebugText("FPS: " + std::to_string(static_cast<std::int32_t>(FramesPerSecond())), "game", {0, 0},
		                10 * GRAPHIC_SCALE);
	}

private:
	sf::Sprite background;
};
