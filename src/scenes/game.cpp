#include "game.h"

#include "objects/hole.h"
#include "objects/objects.h"

static void init();
static void input();
static void checkCollision(Object& object);
static void drawGame(Texture2D background);
static void drawMenu(Font font);

extern Hole hole;
extern Object bonefires[maxBonefires];
extern Object palmtrees[maxPalmtrees];
extern Object trees[maxTrees];


void runGame()
{
	init();

	Texture2D palmtree = LoadTexture("res/palmtree.png");
	Texture2D tree = LoadTexture("res/tree.png");
	Texture2D bonefire = LoadTexture("res/bonefire.png");
	Texture2D sand = LoadTexture("res/sand.png");

	Font font = LoadFont("res/font.ttf");

	Scene currentScene = Menu;

	palmtree.width = static_cast<int>(palmtree.width * 0.2f);
	palmtree.height = static_cast<int>(palmtree.height * 0.2f);



	createHole(hole, BLUE);

	for (int i = 0; i < maxBonefires; i++)
	{
		createObject(bonefires[i], 10, bonefire);
	}

	for (int i = 0; i < maxPalmtrees; i++)
	{
		createObject(palmtrees[i], 15, palmtree);
	}

	for (int i = 0; i < maxTrees; i++)
	{
		createObject(trees[i], 20, tree);
	}

	bool isGameOver = false;

	while (!WindowShouldClose() && !isGameOver)
	{

		input();

		for (int i = 0; i < maxBonefires; i++)
		{
			checkCollision(bonefires[i]);
		}

		for (int i = 0; i < maxPalmtrees; i++)
		{
			checkCollision(palmtrees[i]);
		}

		for (int i = 0; i < maxTrees; i++)
		{
			checkCollision(trees[i]);
		}

		switch (currentScene)
		{
		case Menu:

			drawMenu(font);

			break;
		case Play:

			drawGame(sand);

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

void checkCollision(Object& object)
{
	if (CheckCollisionCircles(hole.pos, hole.radius * 0.75f, object.pos, object.requiredRad) && object.isActive && hole.radius >= object.requiredRad)
	{
		switch (static_cast<int>(object.requiredRad))
		{
		case 10:
			hole.radius += 1;
			break;
		case 15:
			hole.radius += 3;
			break;
		case 20:
			hole.radius += 5;
			break;
		default:
			break;
		}

		hole.speed.x--;
		hole.speed.y--;
		object.isActive = false;
	}
}

void drawGame(Texture2D background)
{
	BeginDrawing();
	ClearBackground(DARKGRAY);

	DrawTexture(background, 0, 0, WHITE);

	drawHole();

	drawObjects();

	DrawText(TextFormat("Size: %i", static_cast<int>(hole.radius)), 500, 10, 30, hole.color);
	DrawFPS(10, 10);
	EndDrawing();
}

void drawMenu(Font font)
{
	float titleLength = MeasureTextEx(font, "Hole.io", static_cast<float>(font.baseSize), 20).x;
	float playLength = MeasureTextEx(font, "Play", static_cast<float>(font.baseSize), 0).x;

	BeginDrawing();
	ClearBackground(BLACK);

	DrawTextPro(font, "Hole.io", Vector2{ GetScreenWidth() / 2 - titleLength / 2, static_cast<float>(GetScreenHeight() / 4.5f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 20, YELLOW);

	DrawTextPro(font, "Play", Vector2{ GetScreenWidth() / 2 - playLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, GREEN);

	
	
	EndDrawing();
}
