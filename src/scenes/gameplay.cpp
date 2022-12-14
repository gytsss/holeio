#include "gameplay.h"

#include "objects/hole.h"
#include "objects/objects.h"

namespace tob
{
	static void input();
	static void reset(float& timer);
	static void checkCollisions();
	static void pauseCollisions(Scene& currentScene, float& timer);
	static bool collisionHoleObject(Object& object);
	static void checkWinOrLose(float timer, Scene& currentScene);
	static void drawPause(Font font, Scene& currentScene, float& timer);
	static void drawGame(Texture2D background, Font font, float timer, Texture2D pause);
	static void drawWinOrLoseScreen(Font font);
	static void unloadTextures();


	extern Hole hole;
	extern Object bonefires[maxBonefires];
	extern Object palmtrees[maxPalmtrees];
	extern Object trees[maxTrees];

	static bool pause = false;
	static int currentObjects = 0;
	static bool isGameOver = false;
	static bool win = false;
	static bool lose = false;

	static Texture2D palmtree;
	static Texture2D tree;
	static Texture2D bonefire;
	static Texture2D sand;
	static Texture2D pauseIcon;

	static Color actualSkin;

	void initGameplay(Color skin)
	{
		palmtree = LoadTexture("res/palmtree.png");
		tree = LoadTexture("res/tree.png");
		bonefire = LoadTexture("res/bonefire.png");
		sand = LoadTexture("res/sand.png");
		pauseIcon = LoadTexture("res/pause.png");

		palmtree.width = static_cast<int>(palmtree.width * 0.2f);
		palmtree.height = static_cast<int>(palmtree.height * 0.2f);

		actualSkin = skin;

		createHole(hole, actualSkin);


		createAllObjects(currentObjects, bonefire, palmtree, tree);
	}

	void updateGameplay(Scene& currentScene, float& timer)
	{
		if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ static_cast<float>(GetScreenWidth() - 43), 40 }, 30) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && currentScene == Play)
			pause = !pause;


		if (!pause && currentScene == Play)
		{
			timer -= GetFrameTime();

			input();

			checkCollisions();

			checkObjectsOverlap(bonefire, palmtree, tree);

			checkWinOrLose(timer, currentScene);
		}
	}

	void drawGameplay(Font font, Scene& currentScene, float& timer)
	{
		drawGame(sand, font, timer, pauseIcon);

		if (pause)
			drawPause(font, currentScene, timer );

		drawWinOrLoseScreen(font);
	}

	void closeGameplay()
	{
		unloadTextures();
	}

	void input()
	{
		holeMovement();
	}

	void reset(float& timer)
	{
		currentObjects = 0;
		timer = 0.0f;
		win = false;
		pause = false;
		lose = false;

		createHole(hole, actualSkin);

		createAllObjects(currentObjects, bonefire, palmtree, tree);

	}

	void checkCollisions()
	{
		for (int i = 0; i < maxBonefires; i++)
		{
			if (collisionHoleObject(bonefires[i]))
			{
				eatLogic(1);

				bonefires[i].isActive = false;

				currentObjects--;
			}
		}

		for (int i = 0; i < maxPalmtrees; i++)
		{
			if (collisionHoleObject(palmtrees[i]))
			{
				eatLogic(2);

				palmtrees[i].isActive = false;

				currentObjects--;
			}
		}

		for (int i = 0; i < maxTrees; i++)
		{
			if (collisionHoleObject(trees[i]))
			{
				eatLogic(5);

				trees[i].isActive = false;

				currentObjects--;
			}
		}
	}

	void pauseCollisions(Scene& currentScene, float& timer)
	{
		Rectangle playBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 2.5f), 100, 40 };
		Rectangle exitBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 1.70f), 100, 40 };


		if (CheckCollisionPointRec(GetMousePosition(), playBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			pause = false;

		if (CheckCollisionPointRec(GetMousePosition(), exitBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			
			reset(timer);

			pause = false;
			currentScene = Menu;
		}

	}

	bool collisionHoleObject(Object& object)
	{
		if (CheckCollisionCircles(hole.pos, hole.radius * 0.75f, object.pos, object.requiredRad) && object.isActive && hole.radius >= object.requiredRad)
			return true;
		else
			return false;
	}

	void checkWinOrLose(float timer, Scene& currentScene)
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

	void drawPause(Font font, Scene& currentScene, float& timer)
	{
		float playLength = MeasureTextEx(font, "Play", static_cast<float>(font.baseSize), 0).x;
		float exitLength = MeasureTextEx(font, "Exit", static_cast<float>(font.baseSize), 0).x;


		DrawRectangleGradientEx(Rectangle{ static_cast<float>(GetScreenWidth() / 2 - 250), static_cast<float>(GetScreenHeight() / 2 - 250), 500, 500 }, RED, ORANGE, YELLOW, RED);

		DrawTextPro(font, "Play", Vector2{ GetScreenWidth() / 2 - playLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Exit", Vector2{ GetScreenWidth() / 2 - exitLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		pauseCollisions(currentScene, timer);
	}

	void drawGame(Texture2D background, Font font, float timer, Texture2D pause1)
	{
		DrawTexture(background, 0, 0, WHITE);

		drawHole();

		drawObjects();

		DrawTextEx(font, TextFormat("Score: %i", static_cast<int>(hole.radius - 10)), Vector2{ 500, 10 }, 30, 0, RED);

		DrawTextEx(font, TextFormat("Timer: %i ", static_cast<int>(timer)), Vector2{ 200, 10 }, 30, 0, RED);

		DrawTexture(pause1, GetScreenWidth() - 75, 10, WHITE);

	}

	void drawWinOrLoseScreen(Font font)
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

				DrawTextPro(font, TextFormat("Final score: %i", static_cast<int>(hole.radius - 10.0f)), Vector2{ GetScreenWidth() / 2 - 80.0f, static_cast<float>(GetScreenHeight() / 2.0f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);
			}

			float exitLength = MeasureTextEx(font, "Exit", static_cast<float>(font.baseSize), 0).x;

			DrawTextPro(font, "Exit", Vector2{ GetScreenWidth() / 2 - exitLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		}
	}

	void unloadTextures()
	{
		UnloadTexture(palmtree);
		UnloadTexture(tree);
		UnloadTexture(bonefire);
		UnloadTexture(sand);
		UnloadTexture(pauseIcon);
	}

}