#include "game.h"

#include "objects/hole.h"
#include "objects/objects.h"
#include "credits.h"

namespace tob
{

	static void init();
	static void input();
	static void reset(int& currentObjects, float& timer, Texture2D bonefire, Texture2D palmtree, Texture2D tree, bool& win, bool& pause, bool& lose, Color skin);

	static void drawGame(Texture2D background, Font font, float timer, Texture2D pause);
	static void drawMenu(Font font, Texture2D background);
	
	static void drawDifficultySelector(Font font, float& timer, Texture2D background);
	static void drawPause(Font font, bool& pause);
	static void drawCursor(Texture2D cursor);
	static void drawWinOrLoseScreen(bool win, bool lose, bool& pause, Font font);
	static void drawOptions(Font font, Color& skin, Texture2D background);

	static void menuCollisions(float& titleRotation, float& playRotation, float& creditsRotation, float& exitRotation, float& optionsRotation);
	static void difficultySelectorCollisions(float& easyRotation, float& mediumRotation, float& hardRotation, float& timer);
	static void pauseCollisions(bool& pause);
	static void optionsCollision(float& rotation, Color& skin);

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


			if (!pause)
			{
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

				drawMenu(font, menu);

				break;
			case Play:

				if (!pause)
					timer -= GetFrameTime();

				drawGame(sand, font, timer, pauseIcon);

				if (pause)
					drawPause(font, pause);


				drawWinOrLoseScreen(win, lose, pause, font);

				break;
			case DifficultySelector:

				drawDifficultySelector(font, timer, menu);

				break;
			case Options:

				drawOptions(font, skin, menu);

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

	void drawMenu(Font font, Texture2D background)
	{
		float titleLength = MeasureTextEx(font, "Hole.io", static_cast<float>(font.baseSize), 20).x;
		float playLength = MeasureTextEx(font, "Play", static_cast<float>(font.baseSize), 0).x;
		float optionsLength = MeasureTextEx(font, "Options", static_cast<float>(font.baseSize), 0).x;
		float creditsLength = MeasureTextEx(font, "Credits", static_cast<float>(font.baseSize), 0).x;
		float exitLength = MeasureTextEx(font, "Exit", static_cast<float>(font.baseSize), 0).x;

		float titleRotation = 0;
		float playRotation = 0;
		float optionsRotation = 0;
		float creditsRotation = 0;
		float exitRotation = 0;

		menuCollisions(titleRotation, playRotation, creditsRotation, exitRotation, optionsRotation);

		DrawTexture(background, 0, 0, WHITE);

		DrawTextPro(font, "Hole.io", Vector2{ GetScreenWidth() / 2 - titleLength / 2, static_cast<float>(GetScreenHeight() / 4.5f) }, Vector2{ 0, 0 }, titleRotation, static_cast<float>(font.baseSize), 20, RED);

		DrawTextPro(font, "Play", Vector2{ GetScreenWidth() / 2 - playLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, playRotation, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Options", Vector2{ GetScreenWidth() / 2 - optionsLength / 2, static_cast<float>(GetScreenHeight() / 2.0f) }, Vector2{ 0, 0 }, optionsRotation, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Credits", Vector2{ GetScreenWidth() / 2 - creditsLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, creditsRotation, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Exit", Vector2{ GetScreenWidth() / 2 - exitLength / 2, static_cast<float>(GetScreenHeight() / 1.50f) }, Vector2{ 0, 0 }, exitRotation, static_cast<float>(font.baseSize), 0, BLACK);

	}

	void menuCollisions(float& titleRotation, float& playRotation, float& creditsRotation, float& exitRotation, float& optionsRotation)
	{
		Rectangle titleBox = { static_cast<float>(GetScreenWidth() / 2 - 100), static_cast<float>(GetScreenHeight() / 4.5f), 200, 40 };
		Rectangle playBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 2.5f), 100, 40 };
		Rectangle optionsBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 2.0f), 100, 40 };
		Rectangle creditsBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 1.70f), 100, 40 };
		Rectangle exitBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 1.50f), 100, 40 };


		if (CheckCollisionPointRec(GetMousePosition(), titleBox))
			titleRotation = 15;

		if (CheckCollisionPointRec(GetMousePosition(), playBox))
		{
			playRotation = 15;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				currentScene = DifficultySelector;
		}

		if (CheckCollisionPointRec(GetMousePosition(), optionsBox))
		{
			optionsRotation = 15;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				currentScene = Options;
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

	
	void drawDifficultySelector(Font font, float& timer, Texture2D background)
	{
		float difficultyLength = MeasureTextEx(font, "Select difficulty", static_cast<float>(font.baseSize), 10).x;
		float easyLength = MeasureTextEx(font, "Easy", static_cast<float>(font.baseSize), 0).x;
		float mediumLength = MeasureTextEx(font, "Medium", static_cast<float>(font.baseSize), 0).x;
		float hardLength = MeasureTextEx(font, "Hard", static_cast<float>(font.baseSize), 0).x;


		float easyRotation = 0;
		float mediumRotation = 0;
		float hardRotation = 0;

		difficultySelectorCollisions(easyRotation, mediumRotation, hardRotation, timer);


		DrawTexture(background, 0, 0, WHITE);

		DrawTextPro(font, "Select difficulty", Vector2{ GetScreenWidth() / 2 - difficultyLength / 2, static_cast<float>(GetScreenHeight() / 4.5f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 10, BLACK);

		DrawTextPro(font, "Easy", Vector2{ GetScreenWidth() / 2 - easyLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, easyRotation, static_cast<float>(font.baseSize), 0, GREEN);

		DrawTextPro(font, "Medium", Vector2{ GetScreenWidth() / 2 - mediumLength / 2, static_cast<float>(GetScreenHeight() / 2.0f) }, Vector2{ 0, 0 }, mediumRotation, static_cast<float>(font.baseSize), 0, YELLOW);

		DrawTextPro(font, "Hard", Vector2{ GetScreenWidth() / 2 - hardLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, hardRotation, static_cast<float>(font.baseSize), 0, RED);

		DrawTextPro(font, "Back", Vector2{ 10, static_cast<float>(GetScreenHeight() - 50) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

	}

	void difficultySelectorCollisions(float& easyRotation, float& mediumRotation, float& hardRotation, float& timer)
	{
		Rectangle easyBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 2.5f), 100, 40 };
		Rectangle mediumBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 2.0f), 100, 40 };
		Rectangle hardBox = { static_cast<float>(GetScreenWidth() / 2 - 50), static_cast<float>(GetScreenHeight() / 1.70f), 100, 40 };
		Rectangle backBox = { 0.0f, static_cast<float>(GetScreenHeight() - 50), 80, 40 };


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

		if (CheckCollisionPointRec(GetMousePosition(), backBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			currentScene = Menu;

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
			}

			float exitLength = MeasureTextEx(font, "Exit", static_cast<float>(font.baseSize), 0).x;

			DrawTextPro(font, "Exit", Vector2{ GetScreenWidth() / 2 - exitLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		}
	}

	void drawOptions(Font font, Color& skin, Texture2D background)
	{
		float skinLength = MeasureTextEx(font, "Choose your skin:", static_cast<float>(font.baseSize), 0).x;
		float rotation = 0;


		optionsCollision(rotation, skin);

		DrawTexture(background, 0, 0, WHITE);

		DrawTextPro(font, "The objetive of the game is to 'eat' all the objects on the\nmap, when you eat something, your size increases and you\nmove slower. The difficulty depends on the time you have\nto eat everything.\n Movement: WASD.", Vector2{ 250, static_cast<float>(GetScreenHeight() / 4.0f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, YELLOW);

		DrawTextPro(font, "Choose your skin:", Vector2{ static_cast<float>(GetScreenWidth() / 2 - skinLength / 2), static_cast<float>(GetScreenHeight() / 1.7f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Back", Vector2{ 10, static_cast<float>(GetScreenHeight() - 50) }, Vector2{ 0, 0 }, rotation, static_cast<float>(font.baseSize), 0, BLACK);


		DrawRectangle(150, 500, 40, 40, RED);
		DrawRectangle(300, 500, 40, 40, BLUE);
		DrawRectangle(450, 500, 40, 40, PURPLE);
		DrawRectangle(600, 500, 40, 40, GREEN);
		DrawRectangle(750, 500, 40, 40, WHITE);
		DrawRectangle(900, 500, 40, 40, ORANGE);
		DrawRectangle(1050, 500, 40, 40, SKYBLUE);

	}

	void optionsCollision(float& rotation, Color& skin)
	{
		Rectangle backBox = { 0.0f, static_cast<float>(GetScreenHeight() - 50), 80, 40 };
		Rectangle redBox = { 150, 500, 40, 40 };
		Rectangle blueBox = { 300, 500, 40, 40 };
		Rectangle purpleBox = { 450, 500, 40, 40 };
		Rectangle greenBox = { 600, 500, 40, 40 };
		Rectangle whiteBox = { 750, 500, 40, 40 };
		Rectangle orangeBox = { 900, 500, 40, 40 };
		Rectangle skyblueBox = { 1050, 500, 40, 40 };


		if (CheckCollisionPointRec(GetMousePosition(), backBox))
		{
			rotation = 15;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				currentScene = Menu;
		}

		if (CheckCollisionPointRec(GetMousePosition(), redBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			skin = RED;

		if (CheckCollisionPointRec(GetMousePosition(), blueBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			skin = BLUE;

		if (CheckCollisionPointRec(GetMousePosition(), purpleBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			skin = PURPLE;

		if (CheckCollisionPointRec(GetMousePosition(), greenBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			skin = GREEN;

		if (CheckCollisionPointRec(GetMousePosition(), whiteBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			skin = WHITE;

		if (CheckCollisionPointRec(GetMousePosition(), orangeBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			skin = ORANGE;

		if (CheckCollisionPointRec(GetMousePosition(), skyblueBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			skin = SKYBLUE;


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
