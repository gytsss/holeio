#include "objects.h"


namespace tob
{

	Object bonefires[maxBonefires];
	Object palmtrees[maxPalmtrees];
	Object trees[maxTrees];

	void createObject(Object& object, float requiredRad, Texture2D texture)
	{
		do
		{
			object.pos = { static_cast<float>(rand() % (GetScreenWidth() - 150) + 50), static_cast<float>(rand() % (GetScreenHeight() - 150) + 50) };

		} while (fabs(object.pos.x - GetScreenWidth() / 2) < 50 || fabs(object.pos.y - GetScreenHeight() / 2) < 50);
		

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

	void drawObjects()
	{
		for (int i = 0; i < maxBonefires; i++)
		{
			drawObject(bonefires[i]);
		}

		for (int i = 0; i < maxPalmtrees; i++)
		{
			drawObject(palmtrees[i]);
		}

		for (int i = 0; i < maxTrees; i++)
		{
			drawObject(trees[i]);
		}
	}

	void createAllObjects(int& currentObjects, Texture2D bonefire, Texture2D palmtree, Texture2D tree)
	{
		for (int i = 0; i < maxBonefires; i++)
		{
			createObject(bonefires[i], 10, bonefire);
			currentObjects++;
		}

		for (int i = 0; i < maxPalmtrees; i++)
		{
			createObject(palmtrees[i], 20, palmtree);
			currentObjects++;
		}

		for (int i = 0; i < maxTrees; i++)
		{
			createObject(trees[i], 40, tree);
			currentObjects++;
		}

	}
}
