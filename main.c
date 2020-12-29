#include <stdio.h>
#include <raylib.h>
#include <stdint.h>
#include <time.h>

#include "dict.h"
#include "resources.h"
#include "particles.h"

const int ScreenWidth = 800;
const int ScreenHeight = 600;

int64_t frameCounter = 0;
dictionary *dt = NULL;



typedef struct  TextData{
     char *word;
     int x;
     int y;
     int hit;
     int speed;
     int index;
     int size;
}TextData;


typedef struct Gameplay {
    char **chosen_words;
    TextData *actualWord;
    int hit;
    int score;
}Gameplay;




Gameplay gameplay;
Particle *particleList = NULL;
Particle *RainMJ_BG = NULL;

// gameplay prototypes
int Gameplay_CheckTextBound(Gameplay *gm);
void GameplayResetWord(Gameplay *gm);


// textdata proto
TextData* TextDataInit();
TextData* TextData_Start(const char *text, int x, int y);
void TextData_SetSpeed(TextData *dt, int speed);
void TextData_EditText(TextData *dt, const char *text);




void LogCustom(int msgType, const char *text, va_list args)
{
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);

    switch (msgType)
    {
        case LOG_INFO: printf("[INFO] : "); break;
        case LOG_ERROR: printf("[ERROR]: "); break;
        case LOG_WARNING: printf("[WARN] : "); break;
        case LOG_DEBUG: printf("[DEBUG]: "); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}


int Gameplay_CheckTextBound(Gameplay *gm){
    if(gm->actualWord->x  < 0){
        fprintf(stdout, "FIM");
        GameplayResetWord(gm);
        return 0;
    }

    return 1;
}



TextData* TextDataInit(){
    TextData *tx = NULL;
    tx = malloc(sizeof (TextData));
    tx->x = 0;
    tx->y = 0;
    tx->hit = 0;
    tx->word = NULL;
    tx->speed = 1;
    tx->index = 0;
    tx->size = 0;
    return tx;
}


TextData* TextData_Start(const char *text, int x, int y){
    TextData *self = NULL;
    self = TextDataInit();
    self->x = x;
    self->y = y;
    self->word = calloc(255, sizeof(char));
    self->size = TextLength(text);

    strncpy(self->word, text, 255 - sizeof(text));
    return self;
}

void TextData_SetSpeed(TextData *dt, int speed){
    if(dt->speed == speed) return;
    dt->speed = speed;
}



void TextData_EditText(TextData *dt, const char *text){

    if(dt->word){
        memset(dt->word,0, 255);
        strncpy(dt->word, text, 255);
        dt->size = TextLength(dt->word);
    }
}



int TextData_CheckHit(TextData *dt, char word[]){
    if(strncasecmp(dt->word, word, strlen(dt->word)) == 0){
        return 1;
    }

    return 0;
}

void GameplayResetWord(Gameplay *gm){
    gm->actualWord->x = ScreenWidth + TextLength(gm->actualWord->word);
    gm->actualWord->y = GetRandomValue(0, ScreenHeight);
    TextData_EditText(gm->actualWord, gm->chosen_words[GetRandomValue(0,18)]);
    gameplay.actualWord->hit = 0;
    gameplay.actualWord->index = 0;

}



int main()
{
    srand((unsigned)time(NULL));
    InitWindow(ScreenWidth, ScreenHeight, "Trippy Typing!");
    Resources_Init();

    SetTargetFPS(60);
    SetTraceLogCallback(LogCustom);

    dt = dictionary_start("words");

    gameplay.chosen_words = dictionary_array_random_words(dt, 18);
    gameplay.actualWord = TextData_Start(gameplay.chosen_words[0], ScreenWidth - 50, GetRandomValue(0, ScreenHeight) );

    TextData_SetSpeed( gameplay.actualWord, 1);

   // particleList = Particle_Init(PARTICLES_MAX);
    RainMJ_BG = Particle_Init(PARTICLES_MAX);

    char key_input[255] = {'\0'};
    int  input_size = 0;


    while(!WindowShouldClose()){
        frameCounter++;

        int key = GetKeyPressed();

        if( (frameCounter / 60) % 6 ){
            Particle_Rain(RainMJ_BG, GetRandomValue(0, ScreenWidth),-90, 12, GetRandomValue(50, 700), TEX_MARIJUANA);
        }


        if( (gameplay.actualWord->x) < 0){
            printf("FIM\n");
            GameplayResetWord(&gameplay);
            memset(key_input,'\0',255);
            input_size = 0;

        }else {

            if(key >= 32 && key <= 125){



                if(!gameplay.actualWord->hit){
                    if(key ==  TextToUpper(gameplay.actualWord->word)[gameplay.actualWord->index]){
                         key_input[gameplay.actualWord->index] = key;
                         gameplay.actualWord->index++;

                    }
                }


                printf("SIZE: %d INDEX: %d\n",  gameplay.actualWord->size - 1, gameplay.actualWord->index);
            }




            if(gameplay.actualWord->index >= gameplay.actualWord->size - 1){
                   gameplay.actualWord->hit = 1;

            }

            if(gameplay.actualWord->hit){
                printf("HIT\n");
                GameplayResetWord(&gameplay);
                memset(key_input,'\0',255);
                input_size = 0;
            }

            int i = 0;
            for(i = 0; i < PARTICLES_MAX;i++){
                //Particle_Update(&particleList[i]);
                if(RainMJ_BG[i].ttl == 0){
                    RainMJ_BG[i].ttl = GetRandomValue(0, 850);
                }

                if(RainMJ_BG[i].position.x < 0 || RainMJ_BG[i].position.x > ScreenWidth + 128){
                    RainMJ_BG[i].ttl = 0;
                }else if(RainMJ_BG[i].position.y > ScreenHeight + 128){
                    RainMJ_BG[i].ttl = 0;
                }

                Particle_Update(&RainMJ_BG[i]);
            }

            gameplay.actualWord->x -= gameplay.actualWord->speed;
            //fprintf(stderr, "x:%d y:%d\n", gameplay.actualWord->x, gameplay.actualWord->y);
        }


        key = GetKeyPressed();


        BeginDrawing();
        ClearBackground(BLACK);
        int k;

        for(k = 0; k < PARTICLES_MAX;k++){
            //Particle_Draw(&particleList[i]);


            //Particle_Draw(&RainMJ_BG[k]);
        }

         DrawText(gameplay.actualWord->word, gameplay.actualWord->x ,gameplay.actualWord->y + 2, 30, WHITE);
        DrawText(gameplay.actualWord->word, gameplay.actualWord->x ,gameplay.actualWord->y, 30, GREEN);
        DrawText( TextToLower(key_input), gameplay.actualWord->x ,gameplay.actualWord->y, 30, PINK);


        BeginBlendMode(BLEND_ALPHA);

        EndBlendMode();

        EndDrawing();
    }
    Resources_Unload();
    CloseWindow();

    return 0;
}
