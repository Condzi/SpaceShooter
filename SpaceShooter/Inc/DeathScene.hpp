/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Tags.hpp"

using namespace con;

class DeathScene final :
	public Scene
{
public:
	std::int16_t Tag() const override
	{
		return static_cast<std::int16_t>(Tag::Scene::DEATH);
	}

	void OnEvent(const sf::Event& ev) override;

	void Draw() override
	{
		Scene::Draw();

		RenderDebugText("You scored " + PlayerStats()["score"] + " points!", "default", {20, WindowSize().y / 2.0f - 20}, 20);
		RenderDebugText("Press [ENTER] to play again.", "default", {20, WindowSize().y / 2.0f}, 20);
	}
};
