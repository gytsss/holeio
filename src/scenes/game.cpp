#include "game.h"

#include "objects/hole.h"
#include "objects/objects.h"
#include "credits.h"
#include "options.h"
#include "menu.h"
#include "objects/cursor.h"
#include "gameplay.h"

namespace tob
{
	static void init();

	extern Hole hole;

	Scene currentScene = Menu;

	void runGame()
	{
		Color skin = BLUE;

		init();

		initGameplay(skin);

		Texture2D menu = LoadTexture("res/menu.png");
		Texture2D cursor = LoadTexture("res/cursor.png");

		Font font = LoadFont("res/font.ttf");

		menu.width = GetScreenWidth();
		menu.height = GetScreenHeight();

		bool isFinished = false;
		float timer = 0;


		while (!WindowShouldClose() && !isFinished)
		{

			updateGameplay(currentScene, timer);


			BeginDrawing();
			ClearBackground(DARKGRAY);

			switch (currentScene)
			{
			case Menu:

				drawMenu(font, menu, currentScene);

				break;
			case Play:

				drawGameplay(font, currentScene, timer);
				
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

				isFinished = true;
				
				break;
			default:
				break;
			}

			drawCursor(cursor);

			EndDrawing();
		}

		
		closeGameplay();
		UnloadTexture(cursor);
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

	

}
