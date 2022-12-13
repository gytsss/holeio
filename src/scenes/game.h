#pragma once
#include "raylib.h"

namespace tob
{
	enum Scene
	{
		Menu,
		Play,
		DifficultySelector,
		Options,
		Credits,
		Exit
	};

	const float easyTimer = 70.0f;
	const float mediumTimer = 50.0f;
	const float hardTimer = 35.0f;


	void runGame();

}

