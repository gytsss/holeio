#pragma once
#include "raylib.h"

namespace tob
{
	const int easyTimer = 12000;
	const int mediumTimer = 6000;
	const int hardTimer = 3000;

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

