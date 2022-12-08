#pragma once
#include "hole.h"

namespace tob
{

	const int maxBonefires = 15;
	const int maxPalmtrees = 10;
	const int maxTrees = 5;

	struct Object
	{
		Vector2 pos;
		float requiredRad;
		bool isActive;
		Texture2D texture;
	};

	void createObject(Object& object, float requiredRad, Texture2D texture);
	void drawObject(Object object);
	void drawObjects();
}