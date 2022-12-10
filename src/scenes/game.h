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

	const int easyTimer = 6000;
	const int mediumTimer = 3000;
	const int hardTimer = 500;


	void runGame();

}

