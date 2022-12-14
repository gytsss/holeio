#pragma once
#include "game.h"

#include "objects/button.h"

namespace tob
{
	const int boxSize = 40;

	void drawOptions(Font font, Color& skin, Texture2D background, Scene& currentScene);
	void optionsCollision(float& rotation, Color& skin, Scene& currentScene, Button button);
}