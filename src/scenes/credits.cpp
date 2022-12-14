#include "credits.h"

namespace tob
{
	static void creditsCollisions(float& rotation, Scene& currentScene, Button button1, Button button2, Button button3);


	void drawCredits(Font font, Texture2D background, Scene& currentScene)
	{
		Button allAssets;
		Button itch;
		Button back;

		createButton(allAssets, Vector2{ static_cast<float>(GetScreenWidth() / 2),static_cast<float>(GetScreenHeight() / 3.0f) }, Vector2{ 450, 40 }, "Click here to see all the assets");
		createButton(itch, Vector2{ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 1.70f) }, Vector2{ 400, 40 }, "Click here to see my itch.io");
		createButton(back, Vector2{ 50.0f, static_cast<float>(GetScreenHeight() - 50) }, Vector2{ 80,40 }, "Back");

		float rotation = 0;

		creditsCollisions(rotation, currentScene, allAssets, itch, back);

		DrawTexture(background, 0, 0, WHITE);

		drawButton(allAssets, font);

		drawButton(itch, font);

		drawButton(back, font);
	}

	void creditsCollisions(float& rotation, Scene& currentScene, Button button1, Button button2, Button button3)
	{

		if (checkCollisionMouseButton(button1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			button1.isPressed = true;


		if (checkCollisionMouseButton(button2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			button2.isPressed = true;



		if (checkCollisionMouseButton(button3))
		{
			rotation = 15;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				button3.isPressed = true;
		}

		if (button1.isPressed)
		{
			OpenURL("https://opengameart.org/content/top-down-village-elements");
			OpenURL("https://opengameart.org/content/top-down-foliage-collection");
		}

		if (button2.isPressed)
			OpenURL("https://tgodd.itch.io/");

		if (button3.isPressed)
			currentScene = Menu;
	}
}