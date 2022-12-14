#pragma once
#include "game.h"


namespace tob
{
	void drawMenu(Font font, Texture2D background, Scene& currentScene);

	void menuCollisions(float& titleRotation, float& playRotation, float& creditsRotation, float& exitRotation, float& optionsRotation, Scene& currentScene);
}
