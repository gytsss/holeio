#include "game.h"

#include "objects/hole.h"
#include "objects/objects.h"
#include "credits.h"
#include "options.h"
#include "menu.h"

namespace tob
{

	static void init();
	static void input();
	static void reset(int& currentObjects, float& timer, Texture2D bonefire, Texture2D palmtree, Texture2D tree, bool& win, bool& pause, bool& lose, Color skin);

	static void drawGame(Texture2D background, Font font, float timer, Texture2D pause);
	static void drawPause(Font font, bool& pause);
	static void drawCursor(Texture2D cursor);
	static void drawWinOrLoseScreen(bool win, bool lose, bool& pause, Font font);

	static void pauseCollisions(bool& pause);

	static void checkCollisions(int& currentObjects);
	static bool collisionHoleObject(Object& object);
	static void checkWinOrLose(float& timer, int currentObjects, bool& win, bool& lose);

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
		Texture2D cursor = LoadTexture("res/cursor.png");
		Texture2D pauseIcon = LoadTexture("res/pause.png");
		Texture2D menu = LoadTexture("res/menu.png");

		Font font = LoadFont("res/font.ttf");


		float timer = 0;
		int currentObjects = 0;

		bool isGameOver = false;
		bool win = false;
		bool lose = false;
		bool pause = false;

		Color skin = BLUE;

		palmtree.width = static_cast<int>(palmtree.width * 0.2f);
		palmtree.height = static_cast<int>(palmtree.height * 0.2f);
		menu.width = GetScreenWidth();
		menu.height = GetScreenHeight();


		createHole(hole, skin);


		createAllObjects(currentObjects, bonefire, palmtree, tree);


		while (!WindowShouldClose() && !isGameOver)
		{

			if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ static_cast<float>(GetScreenWidth() - 43), 40 }, 30) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && currentScene == Play)
				pause = !pause;


			if (!pause && currentScene == Play)
			{
				timer -= GetFrameTime();

				input();

				checkCollisions(currentObjects);

				checkObjectsOverlap(bonefire, palmtree, tree);

				checkWinOrLose(timer, currentObjects, win, lose);
			}


			BeginDrawing();
			ClearBackground(DARKGRAY);

			switch (currentScene)
			{
			case Menu:

				reset(currentObjects, timer, bonefire, palmtree, tree, win, pause, lose, skin);

				drawMenu(font, menu, currentScene);

				break;
			case Play:

				drawGame(sand, font, timer, pauseIcon);

				if (pause)
					drawPause(font, pause);

				drawWinOrLoseScreen(win, lose, pause, font);

				break;
			case DifficultySelector:

				drawDifficultySelector(font, timer, menu, currentScene);

				break;
			case Options:

				drawOptions(font, skin, menu, currentScene);

				break;
			case Credits:

				drawCredits(font, menu, currentScene);

				break;
			case Exit:

				isGameOver = true;

				break;
			default:
				break;
			}

			drawCursor(cursor);

			EndDrawing();
		}

		UnloadTexture(palmtree);
		UnloadTexture(tree);
		UnloadTexture(bonefire);
		UnloadTexture(sand);
		UnloadTexture(cursor);
		UnloadTexture(pauseIcon);
		UnloadTexture(menu);

		UnloadFont(font);

		CloseWindow();
	}

	void init()
	{
		const int screenWidth = 1280;
		const int screenHeight = 720;

		InitWindow(screenWidth, screenHeight, "Hole.io 1.1");
		SetWindowState(FLAG_VSYNC_HINT);
		HideCursor();

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

	void reset(int& currentObjects, float& timer, Texture2D bonefire, Texture2D palmtree, Texture2D tree, bool& win, bool& pause, bool& lose, Color skin)
	{
		currentObjects = 0;
		timer = 0.0f;
		win = false;
		pause = false;
		lose = false;

		createHole(hole, skin);

		createAllObjects(currentObjects, bonefire, palmtree, tree);

	}

	void drawGame(Texture2D background, Font font, float timer, Texture2D pause)
	{
		DrawTexture(background, 0, 0, WHITE);

		drawHole();

		drawObjects();

		DrawTextEx(font, TextFormat("Score: %i", static_cast<int>(hole.radius - 10)), Vector2{ 500, 10 }, 30, 0, RED);

		DrawTextEx(font, TextFormat("Timer: %i ", static_cast<int>(timer)), Vector2{ 200, 10 }, 30, 0, RED);

		DrawTexture(pause, GetScreenWidth() - 75, 10, WHITE);

	}

	void drawPause(Font font, bool& pause)
	{
		float playLength = MeasureTextEx(font, "Play", static_cast<float>(font.baseSize), 0).x;
		float exitLength = MeasureTextEx(font, "Exit", static_cast<float>(font.baseSize), 0).x;


		DrawRectangleGradientEx(Rectangle{ static_cast<float>(GetScreenWidth() / 2 - 250), static_cast<float>(GetScreenHeight() / 2 - 250), 500, 500 }, RED, ORANGE, YELLOW, RED);

		DrawTextPro(font, "Play", Vector2{ GetScreenWidth() / 2 - playLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Exit", Vector2{ GetScreenWidth() / 2 - exitLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		pauseCollisions(pause);
	}

	void pauseCollisions(bool& pause)
	{
		Rectangle playBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 2.5f), 100, 40 };
		Rectangle exitBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 1.70f), 100, 40 };


		if (CheckCollisionPointRec(GetMousePosition(), playBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			pause = false;

		if (CheckCollisionPointRec(GetMousePosition(), exitBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			pause = false;
			currentScene = Menu;
		}

	}

	void drawCursor(Texture2D cursor)
	{
		DrawTexture(cursor, static_cast<int>(GetMousePosition().x - 15), static_cast<int>(GetMousePosition().y - 15), WHITE);

	}

	void drawWinOrLoseScreen(bool win, bool lose, bool& pause, Font font)
	{
		if (win || lose)
		{
			pause = true;

			DrawRectangleGradientEx(Rectangle{ static_cast<float>(GetScreenWidth() / 2 - 250), static_cast<float>(GetScreenHeight() / 2 - 250), 500, 500 }, RED, ORANGE, YELLOW, RED);


			if (win)
			{
				float winLength = MeasureTextEx(font, "You win!", static_cast<float>(font.baseSize), 0).x;

				DrawTextPro(font, "You win!", Vector2{ GetScreenWidth() / 2 - winLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);
			}
			else if (lose)
			{
				float loseLength = MeasureTextEx(font, "You lose! No more time!", static_cast<float>(font.baseSize), 0).x;

				DrawTextPro(font, "You lose! No more time!", Vector2{ GetScreenWidth() / 2 - loseLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

				DrawTextPro(font, TextFormat("Final score: %i", static_cast<int>(hole.radius - 10.0f)), Vector2{GetScreenWidth() / 2 - 80.0f, static_cast<float>(GetScreenHeight() / 2.0f)}, Vector2{0, 0}, 0, static_cast<float>(font.baseSize), 0, BLACK);
			}

			float exitLength = MeasureTextEx(font, "Exit", static_cast<float>(font.baseSize), 0).x;

			DrawTextPro(font, "Exit", Vector2{ GetScreenWidth() / 2 - exitLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		}
	}

	void checkCollisions(int& currentObjects)
	{
		for (int i = 0; i < maxBonefires; i++)
		{
			if (collisionHoleObject(bonefires[i]))
			{
				hole.radius += 1;

				hole.speed.x--;
				hole.speed.y--;

				bonefires[i].isActive = false;

				currentObjects--;
			}
		}

		for (int i = 0; i < maxPalmtrees; i++)
		{
			if (collisionHoleObject(palmtrees[i]))
			{
				hole.radius += 2;

				hole.speed.x--;
				hole.speed.y--;

				palmtrees[i].isActive = false;

				currentObjects--;
			}
		}

		for (int i = 0; i < maxTrees; i++)
		{
			if (collisionHoleObject(trees[i]))
			{
				hole.radius += 5;

				hole.speed.x--;
				hole.speed.y--;

				trees[i].isActive = false;

				currentObjects--;
			}
		}
	}

	void checkWinOrLose(float& timer, int currentObjects, bool& win, bool& lose)
	{
		if (timer <= 0 && currentObjects > 0 && currentScene == Play)
		{
			lose = true;

		}
		else if (currentObjects == 0 && timer > 0)
		{
			win = true;

		}
	}

	bool collisionHoleObject(Object& object)
	{
		if (CheckCollisionCircles(hole.pos, hole.radius * 0.75f, object.pos, object.requiredRad) && object.isActive && hole.radius >= object.requiredRad)
			return true;
		else
			return false;
	}
}
