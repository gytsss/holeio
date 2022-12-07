#include "hole.h"

Hole hole;

void createHole(Hole& playerHole, Color color)
{
	playerHole.pos = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };

	playerHole.speed = { 150,150 };

	playerHole.radius = 10;

	playerHole.color = color;
}

void drawHole()
{
	DrawCircle(static_cast<int>(hole.pos.x), static_cast<int>(hole.pos.y), hole.radius + hole.radius / 3, hole.color);
	DrawCircle(static_cast<int>(hole.pos.x), static_cast<int>(hole.pos.y), hole.radius, BLACK);
	DrawCircleLines(static_cast<int>(hole.pos.x), static_cast<int>(hole.pos.y), hole.radius * 0.75f, RED);
}
