#pragma once
#include "raylib.h"

namespace tob
{
	const int easyTimer = 6000;
	const int mediumTimer = 3000;
	const int hardTimer = 2400;

	enum Scene
	{
		Menu,
		Play,
		DifficultySelector,
		Credits,
		Exit
	};

	void runGame();

}

