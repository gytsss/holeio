#pragma once
#include <string>

#include "raylib.h"

using namespace std;

namespace tob
{

	struct Button
	{
		Vector2 pos;
		Vector2 size;
		bool isPressed;
		const char* text;
	};

	void createButton(Button& button, Vector2 pos, Vector2 size, const char* text);

	void drawButton(Button button, Font font);

	bool checkCollisionMouseButton(Button button);
}