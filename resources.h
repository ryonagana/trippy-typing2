#ifndef RESOURCES_H
#define RESOURCES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#define MAX_TEXTURE2D 255
extern Texture2D  textures[MAX_TEXTURE2D];


enum TextureList {
    TEX_MARIJUANA
};


void Resources_Init();
void Resources_Unload();

Texture2D* Resources_GetTexture(int id);
#endif // RESOURCES_H
