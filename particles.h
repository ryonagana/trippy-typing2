#ifndef PARTICLES_H
#define PARTICLES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

#define PARTICLES_MAX 255

typedef struct Particle {
    Vector2 position;
    Vector2 dvel;
    Color color;
    float alpha;
    float size;
    float rot;
    int ttl;
    Texture2D *tex;
}Particle;


Particle* Particle_Init(int count);
void Particle_Set(Particle *ps, Vector2 pos, Vector2 vel, Color col, float alpha, float size, float rotation, int live , int tex);
void Particle_Explosion(Particle *p, int x, int y, int spread, int count, int life, int texture);
void Particle_Update(Particle *p);
void Particle_Rain(Particle *p, int x, int y, int count, int life, int texture);
void Particle_Draw(Particle *p);
Particle* Particle_GetFreeSlot(Particle *p, int max_count);

#endif // PARTICLES_H
