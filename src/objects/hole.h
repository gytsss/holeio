#pragma once
#include <iostream>

#include "raylib.h"


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
	void holeMovement();

	void eatLogic(int sizeIncrease);


	
}
