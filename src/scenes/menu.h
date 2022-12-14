#pragma once
#include "game.h"

namespace tob
{
	void drawMenu(Font font, Texture2D background, Scene& currentScene);
	void drawDifficultySelector(Font font, float& timer, Texture2D background, Scene& currentScene);

	void menuCollisions(float& titleRotation, float& playRotation, float& creditsRotation, float& exitRotation, float& optionsRotation, Scene& currentScene);
	void difficultySelectorCollisions(float& easyRotation, float& mediumRotation, float& hardRotation, float& timer, Scene& currentScene);
}
