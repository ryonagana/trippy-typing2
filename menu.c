#include "menu.h"
#include "fx.h"

static Menu *main_menu;
static Font menuFont;


static void menu_newgame_callback(void *data){

}


static Menu* Menu_Init(){
    Menu *m = NULL;

    m = malloc(sizeof (Menu));

    if(!m){
        fprintf(stdout,"Error Trying to Allocate Menu!");
        return m;
    }

    m->cursor_x = 0;
    m->cursor_y = 0;
    m->count_items = 0;

    m->items = calloc(MAX_ITEMS, sizeof(MenuItem));

    m->x = 0;
    m->y = 0;

    return m;
}

Menu *Menu_Start(int pos_x, int pos_y)
{
    Menu *m = NULL;

    m = Menu_Init();

    m->x = pos_x;
    m->y = pos_y;
    m->cursor_x = pos_x;
    m->cursor_y  = pos_y;

    return m;
}

void Menu_ItemAdd(Menu *m, int id, const char *name, void (*menu_selected_callback)(void *))
{
    if(m->count_items >= MAX_ITEMS) return;

    m->items[m->count_items].id = id;
    m->items[m->count_items].menu_selected = menu_selected_callback;
    strncpy(m->items[m->count_items].name, name, 56 - strlen(name));
    m->items[m->count_items].x = m->x;
    m->items[m->count_items].y = m->y;
    m->count_items++;
}

void Menu_ItemAdd2(Menu *m, MenuItem *item)
{
    if(m->count_items >= MAX_ITEMS) return;
    memcpy(&m->items[m->count_items + 1], item, sizeof(MenuItem));
}

void Menu_Update(Menu *m)
{
    int i;

    for(i = 0; i < MAX_ITEMS; i++){
       if(&m->items[i] == NULL) continue;

        m->cursor_x = m->x;
        m->cursor_y = m->y;
    }
}

void Menu_Draw(Menu *m)
{
    int i;

    for(i = 0; i < MAX_ITEMS; i++){
       if(&m->items[i] == NULL) continue;
        MenuItem *item = &m->items[i];

        DrawCircle(m->cursor_x, m->cursor_y, 10, RED);
        DrawTextEx(menuFont, item->name, (Vector2){item->x, item->y * i}, 50, 2, WHITE);
        DrawTextEx(menuFont, item->name, (Vector2){item->x, item->y * i + 2}, 50, 2, GREEN);

    }
}

void Menu_Loop()
{
    menuFont = LoadFont("res/hippie.ttf");
    main_menu = Menu_Start(GetScreenWidth() / 2, GetScreenHeight() / 2);
    Menu_ItemAdd(main_menu, 0, "New Game", menu_newgame_callback);
    Menu_ItemAdd(main_menu, 1, "Quit", NULL);
    int64_t frame_counter = 0;


    //ColorPallette p = Fx_FuzzyColors();

    while(!WindowShouldClose()){
        frame_counter++;
        static float frame = 0;
        frame += GetFrameTime();
        int key = GetKeyPressed();




            if(IsKeyPressed(KEY_ENTER)){
                break;
            }

            if(IsKeyPressed(KEY_UP)){
                main_menu->cursor_y += 30;
            }

            if(IsKeyPressed(KEY_DOWN)){
                main_menu->cursor_y -= 30;
            }

            fprintf(stdout, "key %c", key);





        Menu_Update(main_menu);

        BeginDrawing();
        ClearBackground(BLACK);
        Fx_Plasma(GetScreenWidth(),GetScreenHeight(), frame);
        //Fx_LavaLamp(&p, GetScreenWidth(),GetScreenHeight());
        Menu_Draw(main_menu);

        if( ((frame_counter / 60) % 2) == 0){
            DrawText("PRESS ENTER!", GetScreenWidth() / 2 - 50, GetScreenHeight() - 100, 50, RED);
        }

        EndDrawing();
    }

    UnloadFont(menuFont);
}
