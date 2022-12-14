#pragma once
#include "game.h"

#include "objects/button.h"

namespace tob
{
	void drawCredits(Font font, Texture2D background, Scene& currentScene);
	void creditsCollisions(float& rotation, Scene& currentScene, Button button1, Button button2, Button button3);
}