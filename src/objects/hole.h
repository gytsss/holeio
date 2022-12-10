#pragma once
#include "raylib.h"
#include <iostream>
#include "ctime"

namespace tob
{

	struct Hole
	{
		Vector2 pos;
		Vector2 speed;
		float radius;
		Color color;
	};

	void createHole(Hole& hole, Color skin);
	void drawHole();
}
