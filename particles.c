#include "particles.h"
#include "resources.h"

Particle* Particle_Init(int count){



    Particle *self = calloc(count > PARTICLES_MAX ? PARTICLES_MAX: count , sizeof (Particle));
    int i;

    for(i = 0; i < count; i++){

        self[i].position = (Vector2){0,0};
        self[i].dvel = (Vector2){0,0};
        self[i].color = (Color) { GetRandomValue(0,255), GetRandomValue(0,255), GetRandomValue(0,255), 0 };
        self[i].alpha = 1.0f;
        self[i].size = (float)GetRandomValue(0,30) / 20.0f;
        self[i].rot = (float)GetRandomValue(0,3600) / 10;
        self[i].ttl = 0;
        self[i].tex = NULL;
    }

    return self;
}

void Particle_Explosion(Particle *p, int x, int y, int spread, int count, int life, int  texture)
{
    int i;
    Particle *tmp;



    for(i = 0; i < count; i++){
        tmp = Particle_GetFreeSlot(p, PARTICLES_MAX);

        if(tmp != NULL){
            int spread_val_x = x + GetRandomValue(0, spread) - spread / 2;
            int spread_val_y = y + GetRandomValue(0, spread) - spread / 2;
            Color c = (Color){ GetRandomValue(0,255), GetRandomValue(0,255), GetRandomValue(0,255), GetRandomValue(0,255) };
            float size = (float)GetRandomValue(0,30) / 20.0f;
            float speed_x = (float)GetRandomValue(0,100) / 100 - 0.5;
            float speed_y = (float)GetRandomValue(0,100) / 100 - 0.5;
            float rot = (float)GetRandomValue(0,3600) / 10;
            int ttl = life ? life : GetRandomValue(0,50);

            Particle_Set(tmp, (Vector2) { spread_val_x, spread_val_y }, (Vector2){speed_x, speed_y}, c, 1.0f, size, rot, ttl, texture);
        }
    }

}

void Particle_Set(Particle *ps, Vector2 pos, Vector2 vel, Color col, float alpha, float size, float rotation, int live, int tex)
{
    ps->position = pos;
    ps->dvel = vel;
    ps->color = col;
    ps->alpha = alpha;
    ps->size = size;
    ps->rot = rotation;
    ps->ttl = live;
    ps->tex = Resources_GetTexture(tex);
}

void Particle_Update(Particle *p)
{
    p->position.x += p->dvel.x;
    p->position.y += p->dvel.y;
    p->rot += 0.3;
    p->ttl--;
}

Particle *Particle_GetFreeSlot(Particle *p, int max_count)
{

    int i = 0;
    while(p[i].ttl > 0 && i < max_count) i++;
    if(i == max_count) return NULL;
    return &p[i];
}

void Particle_Draw(Particle *p)
{

    if(p->tex == NULL) return;

        if(p->ttl > 0){
            DrawTexturePro(*p->tex, (Rectangle){0.0f, 0.0f,  p->tex->width, p->tex->height},
                           (Rectangle){p->position.x, p->position.y,  p->tex->width * p->size, p->tex->height * p->size},
                           (Vector2){p->tex->width * p->size, p->tex->height * p->size },
                           p->rot, Fade(p->color, p->alpha));
        }

}

void Particle_Rain(Particle *p, int x, int y, int count, int life, int texture)
{
    int i;
    Particle *tmp;



    for(i = 0; i < count; i++){
        tmp = Particle_GetFreeSlot(p, PARTICLES_MAX);
        int spread = GetRandomValue(0, 75);
        if(tmp != NULL){
            int spread_val_x = x + GetRandomValue(0, spread) - spread / 2;
            int spread_val_y = y;
            Color c = (Color){ GetRandomValue(0,255), GetRandomValue(0,255), GetRandomValue(0,255), GetRandomValue(0,255) };
            float size = (float)GetRandomValue(0,30) / 20.0f;
            float speed_x = (float)GetRandomValue(0,300) / 100 - 0.5;
            float speed_y = (float)GetRandomValue(0,300) / 100 - 0.5;
            float rot = (float)GetRandomValue(0,3600) / 10;
            int ttl = life ? life : GetRandomValue(0,450);

            Particle_Set(tmp, (Vector2) { spread_val_x, spread_val_y }, (Vector2){speed_x, speed_y}, c, 1.0f, size, rot, ttl, texture);
        }
    }
}
