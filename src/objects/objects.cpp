#include "objects.h"


void createObject(Object& object, float requiredRad, Texture2D texture)
{
	object.pos = { static_cast<float>(rand() % (GetScreenWidth()-100) + 50), static_cast<float>(rand() % (GetScreenHeight() - 100) + 50) };
	object.requiredRad = requiredRad;
	object.texture = texture;
	object.isActive = true;;
}

void drawObject(Object object)
{
	if (object.isActive)
	{
		DrawTexturePro(object.texture,
			Rectangle{ 0,0, static_cast<float>(object.texture.width), static_cast<float>(object.texture.height) },
			Rectangle{ object.pos.x, object.pos.y, object.requiredRad * 2.5f, object.requiredRad * 2.5f },
			Vector2{ (object.requiredRad * 2.5f) / 2, (object.requiredRad * 2.5f) / 2 },
			0.0f, WHITE);

		DrawCircleLines(static_cast<int>(object.pos.x), static_cast<int>(object.pos.y), object.requiredRad, RED);
	}
}
