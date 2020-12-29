#include "resources.h"
Texture2D  textures[MAX_TEXTURE2D] = {0};

void Resources_Init()
{
    textures[TEX_MARIJUANA] = LoadTexture("res/mj.png");
}

Texture2D *Resources_GetTexture(int id)
{
    if(&textures[id] == NULL) return  NULL;
    return &textures[id];
}

void Resources_Unload()
{
    int i;

    for(i = 0; i < MAX_TEXTURE2D;i++){
        if(&textures[i] != NULL){
            UnloadTexture(textures[i]);
        }
    }
}
