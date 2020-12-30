#ifndef FX_H
#define FX_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <raylib.h>
#include <math.h>


typedef struct ColorPallette {
    uint32_t r[256];
    uint32_t g[256];
    uint32_t b[256];
    double fuzzyness;
}ColorPallette;

ColorPallette Fx_FuzzyColors();


void Fx_LavaLamp(ColorPallette *p, int width, int height);
void Fx_Plasma(int width, int height, float frame_counter);
double fx_calc_dist(float x1, float y1, float x2, float y2);

#endif // FX_H
