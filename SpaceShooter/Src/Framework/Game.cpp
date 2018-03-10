/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <SFML/System/Err.hpp> // Redirect errors

#include "Framework/Game.hpp"

namespace con
{
	Game::Game()
	{
		sf::err().rdbuf(nullptr);

		renderWindow.create({400, 600}, "Space Shooter", sf::Style::Close);
		renderWindow.setFramerateLimit(60);

		initGlobalPointers();
	}

	void Game::Run()
	{
		sf::Clock deltaClock;
		auto& shouldExit = priv::Global().Exit;
		auto& frameDelta = priv::Global().FrameDelta;

		while (!shouldExit)
		{
			frameDelta = deltaClock.restart().asSeconds();

			eventPoll();

			sceneManager.Update();

			renderWindow.clear();
			sceneManager.Draw();
			renderWindow.display();
		}

		renderWindow.close();
	}

	void Game::initGlobalPointers()
	{
		priv::GlobalPointers::ResourceStorage = &resourceStorage;
		priv::GlobalPointers::SceneManager = &sceneManager;
		priv::GlobalPointers::RenderWindow = &renderWindow;
		priv::GlobalPointers::PlayerStats = &playerStats;
	}

	void Game::eventPoll()
	{
		sf::Event ev;
		while (renderWindow.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				priv::Global().Exit = true;

			sceneManager.OnEvent(ev);
		}
	}
}
