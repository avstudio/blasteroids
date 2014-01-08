#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "player.h"

void drawPlayer(Player *p)
{
    //al_draw_filled_rectangle(player->x, player->y, player->x + player->width, player->y + player->height, player->color);
    al_draw_line(p->x - 8 , p->y + 9  ,  p->x      ,  p->y - 11  ,  p->color, 3.0f);
    al_draw_line(p->x     , p->y - 11 ,  p->x + 8  ,  p->y + 9   ,  p->color, 3.0f);
    al_draw_line(p->x - 6 , p->y + 4  ,  p->x - 1  ,  p->y + 4   ,  p->color, 3.0f);
    al_draw_line(p->x + 6 , p->y + 4  ,  p->x + 1  ,  p->y + 4   ,  p->color, 3.0f);
}

void movePlayerRight(Player *player)
{
    player->x += player->speed;
}
void movePlayerLeft(Player *player)
{
    player->x -= player->speed;
}

void movePlayerUp(Player *player)
{
    player->y -= player->speed;
}

void movePlayerDown(Player *player)
{
    player->y += player->speed;
}