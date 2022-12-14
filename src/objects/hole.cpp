#include "hole.h"

namespace tob
{

	static void moveUp();
	static void moveDown();
	static void moveLeft();
	static void moveRight();


	Hole hole;

	void createHole(Hole& playerHole, Color skin)
	{
		playerHole.pos = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };

		playerHole.speed = { 150,150 };

		playerHole.radius = 10;

		playerHole.color = skin;
	}

	void drawHole()
	{
		DrawCircle(static_cast<int>(hole.pos.x), static_cast<int>(hole.pos.y), hole.radius + hole.radius / 3, hole.color);
		DrawCircle(static_cast<int>(hole.pos.x), static_cast<int>(hole.pos.y), hole.radius, BLACK);

	}

	void holeMovement()
	{
		if (IsKeyDown(KEY_W) && hole.pos.y > 0)
			moveUp();

		if (IsKeyDown(KEY_S) && hole.pos.y < GetScreenHeight())
			moveDown();

		if (IsKeyDown(KEY_A) && hole.pos.x > 0)
			moveLeft();

		if (IsKeyDown(KEY_D) && hole.pos.x < GetScreenWidth())
			moveRight();
	}

	void eatLogic(int sizeIncrease)
	{
		hole.radius += sizeIncrease;

		hole.speed.x--;
		hole.speed.y--;
	}

	void moveUp()
	{
		hole.pos.y -= 1 * hole.speed.y * GetFrameTime();
	}

	void moveDown()
	{
		hole.pos.y += 1 * hole.speed.y * GetFrameTime();
	}

	void moveLeft()
	{
		hole.pos.x -= 1 * hole.speed.x * GetFrameTime();
	}

	void moveRight()
	{
		hole.pos.x += 1 * hole.speed.x * GetFrameTime();
	}



}
