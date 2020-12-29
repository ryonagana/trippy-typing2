#ifndef FX_H
#define FX_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <raylib.h>
#include <math.h>


typedef struct Plasma {
    uint32_t r[256];
    uint32_t g[256];
    uint32_t b[256];
    double fuzzyness;
}Plasma;

Plasma Fx_FuzzyColors();

void Fx_Plasma(Plasma *p, int width, int height);

#endif // FX_H
