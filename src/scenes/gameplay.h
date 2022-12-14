#pragma once
#include "raylib.h"
#include "game.h"


namespace tob
{
	void initGameplay(Color skin);
	void updateGameplay(Scene& currentScene, float& timer);
	void drawGameplay(Font font, Scene& currentScene, float& timer);
	void closeGameplay();

}