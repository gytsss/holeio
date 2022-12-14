#include "cursor.h"

namespace tob
{
	void drawCursor(Texture2D cursor)
	{
		DrawTexture(cursor, static_cast<int>(GetMousePosition().x - 15), static_cast<int>(GetMousePosition().y - 15), WHITE);
	}

}