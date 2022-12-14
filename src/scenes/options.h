#pragma once
#include "game.h"

namespace tob
{
	void drawOptions(Font font, Color& skin, Texture2D background, Scene& currentScene);
	void optionsCollision(float& rotation, Color& skin, Scene& currentScene);
}