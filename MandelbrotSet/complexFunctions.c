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

void MapSet(int** map, int screenHeight, Vector2 center, float zoom, Vector2 target) {
	for (int x = 0; x < screenHeight * 3 / 2; ++x) {
		for (int y = 0; y < screenHeight; ++y) {
			_C_float_complex a, c;
			a._Val[0] = ((((float)x + (target.x - screenHeight * 3 / 4)) * 2 / screenHeight) - center.x) / zoom; a._Val[1] = ((((float)y + (target.y - screenHeight / 2)) * 2 / screenHeight)  - center.y) / zoom;
			c._Val[0] = a._Val[0]; c._Val[1] = a._Val[1];
			map[x][y] = NumberOfIterationOutOf1000(a, c);
		}
	}
}

void DrawSet(int** map, int screenHeight) {
	for (int x = 0; x < screenHeight * 3 / 2; ++x) {
		for (int y = 0; y < screenHeight; ++y) {
			if (map[x][y] >= 1000) {
				DrawPixel(x, y, BLACK);
			}
			else {
				DrawPixel(x, y, WHITE);
			}
		}
	}
}