#include <complex.h>
#include <math.h>
#include "raylib.h"

_C_float_complex SumOfComplex(_C_float_complex a, _C_float_complex b) {
	return (_C_float_complex) { a._Val[0] + b._Val[0], a._Val[1] + b._Val[1] };
}

_C_float_complex SquareComplex(_C_float_complex a) {
	return (_C_float_complex) { a._Val[0] * a._Val[0] - a._Val[1] * a._Val[1], 2 * a._Val[0] * a._Val[1] };
}

float SquaredAbs(_C_float_complex a) {
	return (a._Val[0] * a._Val[0] + a._Val[1] * a._Val[1]);
}

int NumberOfIterationOutOf1000(_C_float_complex a, _C_float_complex c) {
	int i = 0;
	while (i < 1000 && SquaredAbs(a) < 4) {
		a = SquareComplex(a);
		a = SumOfComplex(a, c);
		++i;
	}
	return i;
}

void DrawSet(int** map, int screenHeight, int screenWidth) {
	for (int x = 0; x < screenWidth; ++x) {
		for (int y = 0; y < screenHeight; ++y) {
			if (map[x][y] >= 1000) {
				DrawPixel(x, y, BLACK);
			}
			else {
				Color color = { 255, 255, 255, 255 };
				color.g = 255 - 5 * (map[x][y]); color.r = 255; color.b = 255; color.a = 255;
				DrawPixel(x, y, color);
			}
		}
	}
}


void MapSet(int** map, int screenHeight, int screenWidth, float zoom, Vector2 leftUp) {
	for (int x = 0; x < screenWidth; ++x) {
		for (int y = 0; y < screenHeight; ++y) {
			_C_float_complex a, c;

			a._Val[0] = ((float)x / zoom + leftUp.x) / (screenWidth / 3) - 2.0f; a._Val[1] = ((float)y / zoom + leftUp.y) / (screenHeight / 2) - 1.0f;
			c._Val[0] = a._Val[0]; c._Val[1] = a._Val[1];

			map[x][y] = NumberOfIterationOutOf1000(a, c);
		}
	}
}