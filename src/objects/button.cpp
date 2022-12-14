#include "button.h"

namespace tob
{

	void createButton(Button& button, Vector2 pos, Vector2 size, const char* text)
	{
		button.pos = pos;
		button.size = size;
		button.text = text;
	}

	void drawButton(Button button, Font font)
	{
		float length = MeasureTextEx(font, button.text, static_cast<float>(font.baseSize), 0).x;

		DrawTextPro(font, button.text, Vector2{ button.pos.x - length / 2, button.pos.y }, Vector2{ 0, 0 }, 0, static_cast<float>(font.baseSize), 0, BLACK);

	}

	bool checkCollisionMouseButton(Button button)
	{
		if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ button.pos.x, button.pos.y, button.size.x, button.size.y })
		{
			return true;
		}

		return false;
	}
}
