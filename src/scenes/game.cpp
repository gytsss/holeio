#include "game.h"

#include "objects/hole.h"
#include "objects/objects.h"

static void init();
static void input();
static void checkCollision(Object& object);

extern Hole hole;



void runGame()
{
	init();

	Texture2D palmtree = LoadTexture("res/palmtree.png");

	palmtree.width = static_cast<int>(palmtree.width * 0.2f);
	palmtree.height = static_cast<int>(palmtree.height * 0.2f);


	createHole(hole, BLUE);

	Object palmtrees[maxPalmtrees];
	

	for (int i = 0; i < maxPalmtrees; i++)
	{
		createObject(palmtrees[i], 10, palmtree);
	}



	while (!WindowShouldClose())
	{

		input();

		for (int i = 0; i < maxPalmtrees; i++)
		{
			checkCollision(palmtrees[i]);
		}

		BeginDrawing();
		ClearBackground(DARKGREEN);

		drawHole();

		for (int i = 0; i < maxPalmtrees; i++)
		{
			drawObject(palmtrees[i]);
		}


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
#pragma warning( push )
#pragma warning( disable : 4244)
	srand(time(NULL));
#pragma warning( pop ) 
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

void checkCollision(Object& object)
{
	if (CheckCollisionCircles(hole.pos, hole.radius, object.pos, object.requiredRad) && object.isActive)
	{
		hole.radius += 1;
		hole.speed.x--;
		hole.speed.y--;
		object.isActive = false;
	}
}
