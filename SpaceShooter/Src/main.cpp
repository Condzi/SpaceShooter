/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Framework/Game.hpp"

#include "PlayScene.hpp"

int main()
{
	Game game;
	game.StartWithScene<PlayScene>();
	game.Run();
}
