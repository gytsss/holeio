#pragma once
#include "hole.h"

const int maxPalmtrees = 20;
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