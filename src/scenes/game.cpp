#include "game.h"

#include "objects/hole.h"
#include "objects/objects.h"

static void init();
static void input();
static void drawGame(Texture2D background, Font font, int timer);
static void drawMenu(Font font);
static void menuCollisions(float& titleRotation, float& playRotation, float& creditsRotation, float& exitRotation);
static bool checkCollision(Object& object);

extern Hole hole;
extern Object bonefires[maxBonefires];
extern Object palmtrees[maxPalmtrees];
extern Object trees[maxTrees];

Scene currentScene = Menu;

void runGame()
{
	init();

	Texture2D palmtree = LoadTexture("res/palmtree.png");
	Texture2D tree = LoadTexture("res/tree.png");
	Texture2D bonefire = LoadTexture("res/bonefire.png");
	Texture2D sand = LoadTexture("res/sand.png");

	Font font = LoadFont("res/font.ttf");

	int timer = 600;
	bool isGameOver = false;
	int currentObjects = 0;

	palmtree.width = static_cast<int>(palmtree.width * 0.2f);
	palmtree.height = static_cast<int>(palmtree.height * 0.2f);



	createHole(hole, BLUE);

	for (int i = 0; i < maxBonefires; i++)
	{
		createObject(bonefires[i], 10, bonefire);
		currentObjects++;
	}

	for (int i = 0; i < maxPalmtrees; i++)
	{
		createObject(palmtrees[i], 20, palmtree);
		currentObjects++;
	}

	for (int i = 0; i < maxTrees; i++)
	{
		createObject(trees[i], 40, tree);
		currentObjects++;
	}


	while (!WindowShouldClose() && !isGameOver)
	{

		input();

		for (int i = 0; i < maxBonefires; i++)
		{
			if (checkCollision(bonefires[i]))
			{
				hole.radius += 1;

				hole.speed.x--;
				hole.speed.y--;

				bonefires[i].isActive = false;
			}
		}

		for (int i = 0; i < maxPalmtrees; i++)
		{
			if (checkCollision(palmtrees[i]))
			{
				hole.radius += 2;

				hole.speed.x--;
				hole.speed.y--;

				palmtrees[i].isActive = false;
			}
		}

		for (int i = 0; i < maxTrees; i++)
		{
			if (checkCollision(trees[i]))
			{
				hole.radius += 5;

				hole.speed.x--;
				hole.speed.y--;

				trees[i].isActive = false;
			}
		}

		if (timer <= 0 && currentObjects > 0)
		{
			currentScene = Menu;
		}


		switch (currentScene)
		{
		case Menu:

			drawMenu(font);

			break;
		case Play:
			timer--;
			drawGame(sand, font, timer);


			break;

		case Credits:

			break;
		case Exit:
			isGameOver = true;

			break;
		default:
			break;
		}



	}

	CloseWindow();
}

void init()
{
	const int screenWidth = 1280;
	const int screenHeight = 720;

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

bool checkCollision(Object& object)
{
	if (CheckCollisionCircles(hole.pos, hole.radius * 0.75f, object.pos, object.requiredRad) && object.isActive && hole.radius >= object.requiredRad)
	{


		return true;

	}
	else
	{
		return false;
	}
}

void drawGame(Texture2D background, Font font, int timer)
{
	BeginDrawing();
	ClearBackground(DARKGRAY);

	DrawTexture(background, 0, 0, WHITE);

	drawHole();

	drawObjects();

	DrawTextEx(font, TextFormat("Size: %i", static_cast<int>(hole.radius)), Vector2{ 500, 10 }, 30, 0, RED);

	DrawTextEx(font, TextFormat("Timer: %i ", timer / 60), Vector2{ 200, 10 }, 30, 0, RED);

	DrawFPS(10, 10);
	EndDrawing();
}

void drawMenu(Font font)
{
	float titleLength = MeasureTextEx(font, "Hole.io", static_cast<float>(font.baseSize), 20).x;
	float playLength = MeasureTextEx(font, "Play", static_cast<float>(font.baseSize), 0).x;
	float creditsLength = MeasureTextEx(font, "Credits", static_cast<float>(font.baseSize), 0).x;
	float exitLength = MeasureTextEx(font, "Exit", static_cast<float>(font.baseSize), 0).x;

	float titleRotation = 0;
	float playRotation = 0;
	float creditsRotation = 0;
	float exitRotation = 0;

	BeginDrawing();
	ClearBackground(BLACK);

	menuCollisions(titleRotation, playRotation, creditsRotation, exitRotation);

	DrawTextPro(font, "Hole.io", Vector2{ GetScreenWidth() / 2 - titleLength / 2, static_cast<float>(GetScreenHeight() / 4.5f) }, Vector2{ 0, 0 }, titleRotation, static_cast<float>(font.baseSize), 20, YELLOW);

	DrawTextPro(font, "Play", Vector2{ GetScreenWidth() / 2 - playLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, playRotation, static_cast<float>(font.baseSize), 0, GREEN);

	DrawTextPro(font, "Credits", Vector2{ GetScreenWidth() / 2 - creditsLength / 2, static_cast<float>(GetScreenHeight() / 2.0f) }, Vector2{ 0, 0 }, creditsRotation, static_cast<float>(font.baseSize), 0, GREEN);

	DrawTextPro(font, "Exit", Vector2{ GetScreenWidth() / 2 - exitLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, exitRotation, static_cast<float>(font.baseSize), 0, GREEN);



	EndDrawing();
}

void menuCollisions(float& titleRotation, float& playRotation, float& creditsRotation, float& exitRotation)
{
	Rectangle titleBox = { static_cast<float>(GetScreenWidth() / 2 - 100), static_cast<float>(GetScreenHeight() / 4.5f), 200, 40 };
	Rectangle playBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 2.5f), 100, 40 };
	Rectangle creditsBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 2.0f), 100, 40 };
	Rectangle exitBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 1.70f), 100, 40 };

	DrawRectangleLinesEx(titleBox, 1, RED);
	DrawRectangleLinesEx(playBox, 1, RED);
	DrawRectangleLinesEx(creditsBox, 1, RED);
	DrawRectangleLinesEx(exitBox, 1, RED);


	if (CheckCollisionPointRec(GetMousePosition(), titleBox))
		titleRotation = 15;

	if (CheckCollisionPointRec(GetMousePosition(), playBox))
	{
		playRotation = 15;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			currentScene = Play;
	}

	if (CheckCollisionPointRec(GetMousePosition(), creditsBox))
	{
		creditsRotation = 15;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			currentScene = Credits;
	}

	if (CheckCollisionPointRec(GetMousePosition(), exitBox))
	{
		exitRotation = 15;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			currentScene = Exit;
	}
}
