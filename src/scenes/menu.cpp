#include "menu.h"

namespace tob
{
	static void menuCollisions(float& titleRotation, float& playRotation, float& creditsRotation, float& exitRotation, float& optionsRotation, Scene& currentScene);
	static void difficultySelectorCollisions(float& easyRotation, float& mediumRotation, float& hardRotation, float& timer, Scene& currentScene);


	void drawMenu(Font font, Texture2D background, Scene& currentScene)
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

		menuCollisions(titleRotation, playRotation, creditsRotation, exitRotation, optionsRotation, currentScene);

		DrawTexture(background, 0, 0, WHITE);

		DrawTextPro(font, "Hole.io", Vector2{ GetScreenWidth() / 2 - titleLength / 2, static_cast<float>(GetScreenHeight() / 4.5f) }, Vector2{ 0, 0 }, titleRotation, static_cast<float>(font.baseSize), 20, RED);

		DrawTextPro(font, "Play", Vector2{ GetScreenWidth() / 2 - playLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, playRotation, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Options", Vector2{ GetScreenWidth() / 2 - optionsLength / 2, static_cast<float>(GetScreenHeight() / 2.0f) }, Vector2{ 0, 0 }, optionsRotation, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Credits", Vector2{ GetScreenWidth() / 2 - creditsLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, creditsRotation, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Exit", Vector2{ GetScreenWidth() / 2 - exitLength / 2, static_cast<float>(GetScreenHeight() / 1.50f) }, Vector2{ 0, 0 }, exitRotation, static_cast<float>(font.baseSize), 0, BLACK);

	}

	void menuCollisions(float& titleRotation, float& playRotation, float& creditsRotation, float& exitRotation, float& optionsRotation, Scene& currentScene)
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

	void drawDifficultySelector(Font font, float& timer, Texture2D background, Scene& currentScene)
	{
		float difficultyLength = MeasureTextEx(font, "Select difficulty", static_cast<float>(font.baseSize), 10).x;
		float easyLength = MeasureTextEx(font, "Easy", static_cast<float>(font.baseSize), 0).x;
		float mediumLength = MeasureTextEx(font, "Medium", static_cast<float>(font.baseSize), 0).x;
		float hardLength = MeasureTextEx(font, "Hard", static_cast<float>(font.baseSize), 0).x;


		float easyRotation = 0;
		float mediumRotation = 0;
		float hardRotation = 0;

		difficultySelectorCollisions(easyRotation, mediumRotation, hardRotation, timer, currentScene);


		DrawTexture(background, 0, 0, WHITE);

		DrawTextPro(font, "Select difficulty", Vector2{ GetScreenWidth() / 2 - difficultyLength / 2, static_cast<float>(GetScreenHeight() / 4.5f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 10, BLACK);

		DrawTextPro(font, "Easy", Vector2{ GetScreenWidth() / 2 - easyLength / 2, static_cast<float>(GetScreenHeight() / 2.5f) }, Vector2{ 0, 0 }, easyRotation, static_cast<float>(font.baseSize), 0, GREEN);

		DrawTextPro(font, "Medium", Vector2{ GetScreenWidth() / 2 - mediumLength / 2, static_cast<float>(GetScreenHeight() / 2.0f) }, Vector2{ 0, 0 }, mediumRotation, static_cast<float>(font.baseSize), 0, YELLOW);

		DrawTextPro(font, "Hard", Vector2{ GetScreenWidth() / 2 - hardLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, hardRotation, static_cast<float>(font.baseSize), 0, RED);

		DrawTextPro(font, "Back", Vector2{ 10, static_cast<float>(GetScreenHeight() - 50) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

	}

	void difficultySelectorCollisions(float& easyRotation, float& mediumRotation, float& hardRotation, float& timer, Scene& currentScene)
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

}