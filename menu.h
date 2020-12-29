#ifndef STATE_H
#define STATE_H
#define MAX_ITEMS 12
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

typedef struct MenuItem {
    int id;
    char name[56];
    void (*menu_selected)(void *);
    int x;
    int y;
}MenuItem;

typedef struct Menu{
    MenuItem *items;
    int cursor_x;
    int cursor_y;
    int x;
    int y;
    int count_items;

}Menu;


Menu *Menu_Start(int pos_x, int pos_y);
void Menu_ItemAdd(Menu  *m, int id, const char *name,  void (*menu_selected_callback)(void *));
void Menu_ItemAdd2(Menu  *m, MenuItem *item);

void Menu_Update(Menu* m);
void Menu_Draw(Menu* m);


void Menu_Loop();

#endif // STATE_H
