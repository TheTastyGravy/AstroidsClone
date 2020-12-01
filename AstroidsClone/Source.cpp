#include <raylib.h>

int main()
{
	InitWindow(500, 500, "name");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);
		DrawFPS(10, 10);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}