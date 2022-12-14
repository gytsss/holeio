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

	void checkObjectsOverlap(Texture2D bonefire, Texture2D palmtree, Texture2D tree)
	{
		for (int i = 0; i < maxBonefires; i++)
		{
			//Bonefires overlap
			for (int j = 0; j < maxBonefires; j++)
			{
				for (int k = 0; k < maxPalmtrees; k++)
				{
					while (fabs(bonefires[j].pos.x - palmtrees[k].pos.x) < 50 && fabs(bonefires[j].pos.y - palmtrees[k].pos.y) < 50)
					{
						createObject(bonefires[j], 10, bonefire);
					}
				}

				for (int k = j + 1; k < maxBonefires; k++)
				{
					while (fabs(bonefires[j].pos.x - bonefires[k].pos.x) < 50 && fabs(bonefires[j].pos.y - bonefires[k].pos.y) < 50)
					{
						createObject(bonefires[j], 10, bonefire);
					}
				}

				for (int k = 0; k < maxBonefires; k++)
				{
					while (fabs(bonefires[j].pos.x - trees[k].pos.x) < 75 && fabs(bonefires[j].pos.y - trees[k].pos.y) < 75)
					{
						createObject(bonefires[j], 10, bonefire);
					}
				}
			}

			//Palmtrees overlap
			for (int j = 0; j < maxPalmtrees; j++)
			{
				for (int k = j + 1; k < maxPalmtrees; k++)
				{
					while (fabs(palmtrees[j].pos.x - palmtrees[k].pos.x) < 50 && fabs(palmtrees[j].pos.y - palmtrees[k].pos.y) < 50)
					{
						createObject(palmtrees[j], 20, palmtree);
					}
				}

				for (int k = 0; k < maxTrees; k++)
				{
					while (fabs(palmtrees[j].pos.x - trees[k].pos.x) < 75 && fabs(palmtrees[j].pos.y - trees[k].pos.y) < 75)
					{
						createObject(palmtrees[j], 20, palmtree);
					}
				}
			}

			//Trees overlap
			for (int j = 0; j < maxTrees; j++)
			{
				for (int k = j + 1; k < maxTrees; k++)
				{
					while (fabs(trees[j].pos.x - trees[k].pos.x) < 100 && fabs(trees[j].pos.y - trees[k].pos.y) < 100)
					{
						createObject(trees[j], 40, tree);
					}
				}

			}
		}
	}
}
