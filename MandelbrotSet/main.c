#include <complex.h>
#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "ComplexFunctions.h"

int main(void)
{
	const int screenWidth = 300;
	const int screenHeight = 200;
	const int camSpeed = 3;

	const Vector2 center = { 2, 1 };

	Vector2 rectanglePosition;

	int** map = (int**)malloc(sizeof(int*) * screenHeight * 3 / 2);
	for (int i = 0; i < screenHeight * 3 / 2; ++i) {
		map[i] = (int*)malloc(sizeof(int) * screenHeight);
	}

	InitWindow(screenWidth, screenHeight, "Mandelbrot Set");

	SetTargetFPS(60);

	Camera2D camera;
	camera.offset.x = screenHeight * 3 / 4; camera.offset.y = screenHeight / 2;
	camera.target.x = screenHeight * 3 / 4; camera.target.y = screenHeight / 2;
	camera.zoom = 1.0f;
	camera.rotation = 0.0f;

	float currentZoom = 1.0f, globalZoom = 1.0f, deltaZoom = 0.0f;

	MapSet(map, screenHeight, center, globalZoom, camera.target);

	while (!WindowShouldClose())
	{
		rectanglePosition = GetMousePosition();

		deltaZoom = 0.0f;
		deltaZoom += (float)GetMouseWheelMove() * 0.05f;
		globalZoom += deltaZoom;
		currentZoom += deltaZoom;

		if (IsKeyPressed(KEY_R)) {
			currentZoom = 1.0f;
			Vector2 zoomTarget = rectanglePosition;
			//zoomTarget.x = screenWidth - rectanglePosition.x;
			//zoomTarget.y = screenHeight - rectanglePosition.y;
			MapSet(map, screenHeight, center, globalZoom, zoomTarget);
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);
		
		DrawSet(map, screenHeight);
		DrawRectangleLines(rectanglePosition.x - screenHeight * 3 / 4 / currentZoom, rectanglePosition.y - screenHeight / 2 / currentZoom, screenWidth / currentZoom, screenHeight / currentZoom, RED);

		DrawFPS(10, 10);

		EndDrawing();
		printf_s("%f %f\n%f %f\n\n", rectanglePosition.x, rectanglePosition.y, camera.zoom, currentZoom);
	}

	CloseWindow();

	for (int i = 0; i < screenHeight * 3 / 2; ++i) {
		free(map[i]);
	}
	free(map);

	return 0;
}