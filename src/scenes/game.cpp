#include "game.h"

#include "objects/hole.h"

static void init();
static void input();



extern Hole hole;

void runGame()
{
	init();

	createHole(hole, BLUE);


	while (!WindowShouldClose())
	{

		input();

		BeginDrawing();
		ClearBackground(WHITE);

		drawHole();

		DrawFPS(10, 10);
		EndDrawing();

	}

	CloseWindow();
}

void init()
{
	const int screenWidth = 1280;
	const int screenHeight = 1000;

	InitWindow(screenWidth, screenHeight, "Hole.io");
	SetWindowState(FLAG_VSYNC_HINT);

}

void input()
{
	if (IsKeyDown(KEY_W) && hole.pos.y > 0)
		hole.pos.y -= 1 * hole.speed.y * GetFrameTime();
	if (IsKeyDown(KEY_S) && hole.pos.y < GetScreenHeight())
		hole.pos.y += 1 * hole.speed.y * GetFrameTime();
	if (IsKeyDown(KEY_A) && hole.pos.x > 0)
		hole.pos.x -= 1 * hole.speed.x * GetFrameTime();
	if (IsKeyDown(KEY_D) && hole.pos.x < GetScreenWidth())
		hole.pos.x += 1 * hole.speed.x * GetFrameTime();
}
