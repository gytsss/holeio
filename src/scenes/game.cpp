#include "game.h"

#include "objects/hole.h"
#include "objects/objects.h"

namespace tob
{

	static void init();
	static void input();

	static void drawGame(Texture2D background, Font font, int timer, Texture2D cursor);
	static void drawMenu(Font font, Texture2D cursor);
	static void drawCredits(Font font, Texture2D cursor);
	static void drawDifficultySelector(Font font, Texture2D cursor, int& timer);

	static void menuCollisions(float& titleRotation, float& playRotation, float& creditsRotation, float& exitRotation);
	static void creditsCollisions(float& rotation);
	static void difficultyCollisions(float& easyRotation, float& mediumRotation, float& hardRotation, int& timer);

	static void checkCollisions(int& currentObjects);
	static bool collisionHoleObject(Object& object);
	static void checkObjectsOverlap(Texture2D bonefire, Texture2D palmtree, Texture2D tree);

	static void checkWinOrLose(int& timer, int currentObjects);

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

		Font font = LoadFont("res/font.ttf");



		int timer = 12000;
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


			checkCollisions(currentObjects);

			checkObjectsOverlap(bonefire, palmtree, tree);

			checkWinOrLose(timer, currentObjects);



			switch (currentScene)
			{
			case Menu:

				drawMenu(font, cursor);


				break;
			case Play:
				timer--;

				drawGame(sand, font, timer, cursor);


				break;
			case Difficulty:

				drawDifficultySelector(font, cursor, timer);

				break;
			case Credits:

				drawCredits(font, cursor);

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

	bool collisionHoleObject(Object& object)
	{
		if (CheckCollisionCircles(hole.pos, hole.radius * 0.75f, object.pos, object.requiredRad) && object.isActive && hole.radius >= object.requiredRad)
			return true;
		else
			return false;
	}

	void drawGame(Texture2D background, Font font, int timer, Texture2D cursor)
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		DrawTexture(background, 0, 0, WHITE);

		drawHole();

		drawObjects();

		DrawTextEx(font, TextFormat("Score: %i", static_cast<int>(hole.radius - 10)), Vector2{ 500, 10 }, 30, 0, RED);

		DrawTextEx(font, TextFormat("Timer: %i ", timer / 60), Vector2{ 200, 10 }, 30, 0, RED);

		DrawTexture(cursor, static_cast<int>(GetMousePosition().x - 15), static_cast<int>(GetMousePosition().y - 15), WHITE);

		DrawFPS(10, 10);
		EndDrawing();
	}

	void drawMenu(Font font, Texture2D cursor)
	{
		float titleLength = MeasureTextEx(font, "Hole.io", static_cast<float>(font.baseSize), 20).x;
		float playLength = MeasureTextEx(font, "Play", static_cast<float>(font.baseSize), 0).x;
		float creditsLength = MeasureTextEx(font, "Credits", static_cast<float>(font.baseSize), 0).x;
		float exitLength = MeasureTextEx(font, "Exit", static_cast<float>(font.baseSize), 0).x;

		float titleRotation = 0;
		float playRotation = 0;
		float creditsRotation = 0;
		float exitRotation = 0;

		menuCollisions(titleRotation, playRotation, creditsRotation, exitRotation);

		BeginDrawing();
		ClearBackground(DARKGRAY);


		DrawTextPro(font, "Hole.io", Vector2{ GetScreenWidth() / 2 - titleLength / 2, static_cast<float>(GetScreenHeight() / 4.5f) }, Vector2{ 0, 0 }, titleRotation, static_cast<float>(font.baseSize), 20, YELLOW);

		DrawTextPro(font, "Play", Vector2{ GetScreenWidth() / 2 - playLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, playRotation, static_cast<float>(font.baseSize), 0, GREEN);

		DrawTextPro(font, "Credits", Vector2{ GetScreenWidth() / 2 - creditsLength / 2, static_cast<float>(GetScreenHeight() / 2.0f) }, Vector2{ 0, 0 }, creditsRotation, static_cast<float>(font.baseSize), 0, GREEN);

		DrawTextPro(font, "Exit", Vector2{ GetScreenWidth() / 2 - exitLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, exitRotation, static_cast<float>(font.baseSize), 0, GREEN);

		DrawTexture(cursor, static_cast<int>(GetMousePosition().x - 15), static_cast<int>(GetMousePosition().y - 15), WHITE);

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
				currentScene = Difficulty;
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

	void drawCredits(Font font, Texture2D cursor)
	{
		float creditLength = MeasureTextEx(font, "Click here to see all the assets", static_cast<float>(font.baseSize), 0).x;
		float itchLength = MeasureTextEx(font, "Click here to see my itch.io", static_cast<float>(font.baseSize), 0).x;

		float rotation = 0;

		creditsCollisions(rotation);

		BeginDrawing();
		ClearBackground(DARKGRAY);

		DrawTextPro(font, "Click here to see all the assets", Vector2{ GetScreenWidth() / 2 - creditLength / 2, static_cast<float>(GetScreenHeight() / 4.0f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, YELLOW);

		DrawTextPro(font, "Click here to see my itch.io", Vector2{ GetScreenWidth() / 2 - itchLength / 2, static_cast<float>(GetScreenHeight() / 2.0f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, YELLOW);

		DrawTextPro(font, "Back", Vector2{ 10, static_cast<float>(GetScreenHeight() - 50) }, Vector2{ 0, 0 }, rotation, static_cast<float>(font.baseSize), 0, YELLOW);

		DrawTexture(cursor, static_cast<int>(GetMousePosition().x - 15), static_cast<int>(GetMousePosition().y - 15), WHITE);


		EndDrawing();
	}

	void creditsCollisions(float& rotation)
	{
		Rectangle assetsBox = { static_cast<float>(GetScreenWidth() / 2 - 220), static_cast<float>(GetScreenHeight() / 4.0f), 450, 40 };
		Rectangle itchBox = { static_cast<float>(GetScreenWidth() / 2 - 200), static_cast<float>(GetScreenHeight() / 2.0f), 400, 40 };
		Rectangle backBox = { 0.0f, static_cast<float>(GetScreenHeight() - 50), 80, 40 };

		DrawRectangleLinesEx(assetsBox, 1, RED);
		DrawRectangleLinesEx(itchBox, 1, RED);
		DrawRectangleLinesEx(backBox, 1, RED);




		if (CheckCollisionPointRec(GetMousePosition(), assetsBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			OpenURL("https://opengameart.org/content/top-down-village-elements");
			OpenURL("https://opengameart.org/content/top-down-foliage-collection");
			//OpenURL("");
			//OpenURL("");

		}

		if (CheckCollisionPointRec(GetMousePosition(), itchBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			OpenURL("https://tgodd.itch.io/");
		}

		if (CheckCollisionPointRec(GetMousePosition(), backBox))
		{
			rotation = 15;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				currentScene = Menu;
		}
	}

	void checkWinOrLose(int& timer, int currentObjects)
	{
		if (timer <= 0 && currentObjects > 0 && currentScene == Play)
		{
			currentScene = Menu;
			timer = 1200;
		}
		else if (currentObjects == 0 && timer > 0)
		{
			currentScene = Menu;
			timer = 1200;
		}
	}

	void checkObjectsOverlap(Texture2D bonefire, Texture2D palmtree, Texture2D tree)
	{
		for (int i = 0; i < maxBonefires; i++)
		{
			//Bonefires overlap
			for (int j = 0; j < maxBonefires; j++)
			{
				for (int k = 0; k < maxPalmtrees; k++)
				{
					while (fabs(bonefires[j].pos.x - palmtrees[k].pos.x) < 50 && fabs(bonefires[j].pos.y - palmtrees[k].pos.y) < 50)
					{
						createObject(bonefires[j], 10, bonefire);
					}
				}

				for (int k = j + 1; k < maxBonefires; k++)
				{
					while (fabs(bonefires[j].pos.x - bonefires[k].pos.x) < 50 && fabs(bonefires[j].pos.y - bonefires[k].pos.y) < 50)
					{
						createObject(bonefires[j], 10, bonefire);
					}
				}

				for (int k = 0; k < maxBonefires; k++)
				{
					while (fabs(bonefires[j].pos.x - trees[k].pos.x) < 75 && fabs(bonefires[j].pos.y - trees[k].pos.y) < 75)
					{
						createObject(bonefires[j], 10, bonefire);
					}
				}
			}

			//Palmtrees overlap
			for (int j = 0; j < maxPalmtrees; j++)
			{
				for (int k = j + 1; k < maxPalmtrees; k++)
				{
					while (fabs(palmtrees[j].pos.x - palmtrees[k].pos.x) < 50 && fabs(palmtrees[j].pos.y - palmtrees[k].pos.y) < 50)
					{
						createObject(palmtrees[j], 20, palmtree);
					}
				}

				for (int k = 0; k < maxTrees; k++)
				{
					while (fabs(palmtrees[j].pos.x - trees[k].pos.x) < 75 && fabs(palmtrees[j].pos.y - trees[k].pos.y) < 75)
					{
						createObject(palmtrees[j], 20, palmtree);
					}
				}
			}
			
			//Trees overlap
			for (int j = 0; j < maxTrees; j++)
			{
				for (int k = j + 1; k < maxTrees; k++)
				{
					while (fabs(trees[j].pos.x - trees[k].pos.x) < 100 && fabs(trees[j].pos.y - trees[k].pos.y) < 100)
					{
						createObject(trees[j], 40, tree);
					}
				}

			}
		}
	}

	void drawDifficultySelector(Font font, Texture2D cursor, int& timer)
	{
		float difficultyLength = MeasureTextEx(font, "Select difficulty", static_cast<float>(font.baseSize), 10).x;
		float easyLength = MeasureTextEx(font, "Easy", static_cast<float>(font.baseSize), 0).x;
		float mediumLength = MeasureTextEx(font, "Medium", static_cast<float>(font.baseSize), 0).x;
		float hardLength = MeasureTextEx(font, "Hard", static_cast<float>(font.baseSize), 0).x;
		

		float easyRotation = 0;
		float mediumRotation = 0;
		float hardRotation = 0;

		difficultyCollisions(easyRotation, mediumRotation, hardRotation, timer);

		BeginDrawing();
		ClearBackground(DARKGRAY);

		DrawTextPro(font, "Select difficulty", Vector2{ GetScreenWidth() / 2 - difficultyLength / 2, static_cast<float>(GetScreenHeight() / 4.5f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 10, YELLOW);

		DrawTextPro(font, "Easy", Vector2{ GetScreenWidth() / 2 - easyLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, easyRotation, static_cast<float>(font.baseSize), 0, YELLOW);

		DrawTextPro(font, "Medium", Vector2{ GetScreenWidth() / 2 - mediumLength / 2, static_cast<float>(GetScreenHeight() / 2.0f) }, Vector2{ 0, 0 }, mediumRotation, static_cast<float>(font.baseSize), 0, YELLOW);

		DrawTextPro(font, "Hard", Vector2{ GetScreenWidth() / 2 - hardLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, hardRotation, static_cast<float>(font.baseSize), 0, YELLOW);

		DrawTexture(cursor, static_cast<int>(GetMousePosition().x - 15), static_cast<int>(GetMousePosition().y - 15), WHITE);


		EndDrawing();
	}

	void difficultyCollisions(float& easyRotation, float& mediumRotation, float& hardRotation, int& timer)
	{
		Rectangle easyBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 2.5f), 100, 40 };
		Rectangle mediumBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 2.0f), 100, 40 };
		Rectangle hardBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 1.70f), 100, 40 };

		DrawRectangleLinesEx(easyBox, 1, RED);
		DrawRectangleLinesEx(mediumBox, 1, RED);
		DrawRectangleLinesEx(hardBox, 1, RED);



		if (CheckCollisionPointRec(GetMousePosition(), easyBox))
		{
			easyRotation = 15;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				timer = easyTimer;
				currentScene = Play;
			}
		}

		if (CheckCollisionPointRec(GetMousePosition(), mediumBox))
		{
			mediumRotation = 15;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				timer = mediumTimer;
				currentScene = Play;
			}
		}

		if (CheckCollisionPointRec(GetMousePosition(), hardBox))
		{
			hardRotation = 15;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				timer = hardTimer;
				currentScene = Play;
			}
		}
	}
}
