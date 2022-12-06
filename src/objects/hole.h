#pragma once
#include "raylib.h"

struct Hole
{
	Vector2 pos;
	Vector2 speed;
	float radius;
	Color color;
};

void createHole(Hole& hole, Color color);
void drawHole();
