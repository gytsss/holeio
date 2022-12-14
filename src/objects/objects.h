#pragma once
#include <iostream>
#include <ctime>

#include "raylib.h"



namespace tob
{

	const int maxBonefires = 15;
	const int maxPalmtrees = 10;
	const int maxTrees = 5;
	const int maxObjects = maxBonefires + maxPalmtrees + maxTrees;

	struct Object
	{
		Vector2 pos;
		float requiredRad;
		bool isActive;
		Texture2D texture;
	};

	
	void drawObject(Object object);
	void drawObjects();
	void createAllObjects(int& currentObjects, Texture2D bonefire, Texture2D palmtree, Texture2D tree);
	void checkObjectsOverlap(Texture2D bonefire, Texture2D palmtree, Texture2D tree);

}