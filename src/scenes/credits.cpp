#include "credits.h"

namespace tob
{

	void drawCredits(Font font, Texture2D background, Scene& currentScene)
	{
		float creditLength = MeasureTextEx(font, "Click here to see all the assets", static_cast<float>(font.baseSize), 0).x;
		float itchLength = MeasureTextEx(font, "Click here to see my itch.io", static_cast<float>(font.baseSize), 0).x;

		float rotation = 0;

		creditsCollisions(rotation, currentScene);

		DrawTexture(background, 0, 0, WHITE);

		DrawTextPro(font, "Click here to see all the assets", Vector2{ GetScreenWidth() / 2 - creditLength / 2, static_cast<float>(GetScreenHeight() / 3.0f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Click here to see my itch.io", Vector2{ GetScreenWidth() / 2 - itchLength / 2, static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		DrawTextPro(font, "Back", Vector2{ 10, static_cast<float>(GetScreenHeight() - 50) }, Vector2{ 0, 0 }, rotation, static_cast<float>(font.baseSize), 0, BLACK);

	}

	void creditsCollisions(float& rotation, Scene& currentScene)
	{
		Rectangle assetsBox = { static_cast<float>(GetScreenWidth() / 2 - 220), static_cast<float>(GetScreenHeight() / 3.0f), 450, 40 };
		Rectangle itchBox = { static_cast<float>(GetScreenWidth() / 2 - 200), static_cast<float>(GetScreenHeight() / 1.70f), 400, 40 };
		Rectangle backBox = { 0.0f, static_cast<float>(GetScreenHeight() - 50), 80, 40 };



		if (CheckCollisionPointRec(GetMousePosition(), assetsBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			OpenURL("https://opengameart.org/content/top-down-village-elements");
			OpenURL("https://opengameart.org/content/top-down-foliage-collection");

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
}