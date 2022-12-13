#pragma once
#include "game.h"

namespace tob
{
	void drawCredits(Font font, Texture2D background, Scene& currentScene);
	void creditsCollisions(float& rotation, Scene& currentScene);
}