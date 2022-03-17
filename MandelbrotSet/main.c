#include <complex.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "raylib.h"
#include "ComplexFunctions.h"

int main(void)
{
	const int screenWidth = 600;
	const int screenHeight = 400;

	Vector2 rectanglePosition = { 0,0 }, leftUp = { 0, 0 };

	int** map = (int**)malloc(sizeof(int*) * screenHeight * 3 / 2);
	for (int i = 0; i < screenHeight * 3 / 2; ++i) {
		map[i] = (int*)malloc(sizeof(int) * screenHeight);
	}

	InitWindow(screenWidth, screenHeight, "Mandelbrot Set");

	SetTargetFPS(60);

	float currentZoom = 1.0f, globalZoom = 1.0f, deltaZoom = 0.0f;

	MapSet(map, screenHeight, screenWidth, globalZoom, leftUp);

	while (!WindowShouldClose())
	{
		rectanglePosition = GetMousePosition();

		deltaZoom = 0.0f;
		deltaZoom += (float)GetMouseWheelMove() * 0.25f;
		globalZoom += deltaZoom;
		currentZoom += deltaZoom;
		
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			leftUp.x += (rectanglePosition.x - screenWidth / 2) / globalZoom;
			leftUp.y += (rectanglePosition.y - screenHeight / 2) / globalZoom;

			MapSet(map, screenHeight, screenWidth, globalZoom, leftUp);
			
			currentZoom = 1.0f;
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);
		
		DrawSet(map, screenHeight, screenWidth);

		DrawRectangleLines(rectanglePosition.x - screenWidth / 2 / currentZoom, rectanglePosition.y - screenHeight / 2 / currentZoom, screenWidth / currentZoom, screenHeight / currentZoom, RED);
		
		DrawFPS(10, 10);

		DrawCircleLines(screenWidth / 2, screenHeight / 2, 5, RED);
		
		EndDrawing();
	}

	CloseWindow();

	for (int i = 0; i < screenHeight * 3 / 2; ++i) {
		free(map[i]);
	}
	free(map);

	return 0;
}