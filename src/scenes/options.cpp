#include "options.h"

namespace tob
{

	void drawOptions(Font font, Color& skin, Texture2D background, Scene& currentScene)
	{
		Button back;

		createButton(back, Vector2{ 0.0f, static_cast<float>(GetScreenHeight() - 50) }, Vector2{ 80,40 }, "Back");

		float skinLength = MeasureTextEx(font, "Choose your skin:", static_cast<float>(font.baseSize), 0).x;
		float rotation = 0;


		optionsCollision(rotation, skin, currentScene, back);

		DrawTexture(background, 0, 0, WHITE);

		DrawTextPro(font, "The objetive of the game is to 'eat' all the objects on the\nmap, when you eat something, your size increases and you\nmove slower. The difficulty depends on the time you have\nto eat everything.\n Movement: WASD.", Vector2{ 250, static_cast<float>(GetScreenHeight() / 4.0f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, YELLOW);

		DrawTextPro(font, "Choose your skin:", Vector2{ static_cast<float>(GetScreenWidth() / 2 - skinLength / 2), static_cast<float>(GetScreenHeight() / 1.7f) }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

		drawButton(back, font);

		DrawRectangle(150, 500, boxSize, boxSize, RED);
		DrawRectangle(300, 500, boxSize, boxSize, BLUE);
		DrawRectangle(450, 500, boxSize, boxSize, PURPLE);
		DrawRectangle(600, 500, boxSize, boxSize, GREEN);
		DrawRectangle(750, 500, boxSize, boxSize, WHITE);
		DrawRectangle(900, 500, boxSize, boxSize, ORANGE);
		DrawRectangle(1050, 500, boxSize, boxSize, SKYBLUE);

	}

	void optionsCollision(float& rotation, Color& skin, Scene& currentScene, Button button)
	{
		Rectangle redBox = { 150, 500, 40, 40 };
		Rectangle blueBox = { 300, 500, 40, 40 };
		Rectangle purpleBox = { 450, 500, 40, 40 };
		Rectangle greenBox = { 600, 500, 40, 40 };
		Rectangle whiteBox = { 750, 500, 40, 40 };
		Rectangle orangeBox = { 900, 500, 40, 40 };
		Rectangle skyblueBox = { 1050, 500, 40, 40 };


		if (checkCollisionMouseButton(button))
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
}