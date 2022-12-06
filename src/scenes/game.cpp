#include "game.h"

void runGame()
{
	const int screenWidth = 1280;
	const int screenHeight = 1000;

	InitWindow(screenWidth, screenHeight, "Hole.io");


	while (!WindowShouldClose())
	{

		BeginDrawing();

		
		
		EndDrawing();

	}

	CloseWindow();
}
