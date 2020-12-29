#include "menu.h"
#include "fx.h"

static Menu *main_menu;
static MenuItem  *item_newgame;




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
    m->items[m->count_items].x = m->x + 30;
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
    int key = GetKeyPressed();


    if(key == KEY_UP){
        m->cursor_y += 30;
    }

    if(key == KEY_DOWN){
        m->cursor_y -= 30;
    }



    for(i = 0; i < MAX_ITEMS; i++){
       if(&m->items[i] == NULL) continue;

        m->cursor_x = m->x - 30;
        m->cursor_y = m->y;
    }
}

void Menu_Draw(Menu *m)
{
    int i;

    for(i = 0; i < MAX_ITEMS; i++){
       if(&m->items[i] == NULL) continue;
        MenuItem *item = &m->items[i];
        DrawCircle(m->cursor_x, m->cursor_y, 18, RED);
        DrawText(item->name, item->x,  (item->y * i) + 20, 25, WHITE);


    }
}

void Menu_Loop()
{
    main_menu = Menu_Start(0, 0);
    Menu_ItemAdd(main_menu, 0, "New Game", menu_newgame_callback);
    Menu_ItemAdd(main_menu, 1, "Quit", NULL);

    Plasma p = Fx_FuzzyColors();

    while(!WindowShouldClose()){

        Menu_Update(main_menu);

        BeginDrawing();
        ClearBackground(BLACK);
        Fx_Plasma(&p, GetScreenWidth(),GetScreenHeight());
        Menu_Draw(main_menu);

        EndDrawing();
    }
}
