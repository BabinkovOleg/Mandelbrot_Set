#include <complex.h>
#include "raylib.h"

#pragma once

_C_float_complex SumOfComplex(_C_float_complex a, _C_float_complex b);
_C_float_complex SquareComplex(_C_float_complex a);
float SquaredAbs(_C_float_complex a);
int NumberOfIterationOutOf1000(_C_float_complex a, _C_float_complex c);
void MapSet(int** map, int screenHeight, int screenWidth, float zoom, Vector2 leftUp);
void DrawSet(int** map, int screenHeight, int screenWidth);
