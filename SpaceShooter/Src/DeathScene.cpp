/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/
#include "Framework/SceneManager.hpp"

#include "DeathScene.hpp"
#include "PlayScene.hpp"

void DeathScene::OnEvent(const sf::Event& ev)
{
	if (ev.type == sf::Event::KeyReleased)
	{
		if (ev.key.code == sf::Keyboard::Return)
			SceneManager().SetActiveScene<PlayScene>();
		else if (ev.key.code == sf::Keyboard::Escape)
			Exit();
	}
}
