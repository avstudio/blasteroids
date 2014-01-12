#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "asteroid.h"

void Asteroid_init(Asteroid *a, int x, int y)
{
    a->color = al_map_rgb(3, 173, 49);
    a->live  = true;

    a->motion.speed = (rand() % 5) + 1;
    a->motion.x  = x;
    a->motion.y  = y;
    a->motion.bx = 18;
    a->motion.by = 18;
}


void Asteroid_draw(Asteroid *a)
{
    int x           = a->motion.x;
    int y           = a->motion.y;
    ALLEGRO_COLOR c = a->color;

    al_draw_line(x - 20  ,  y + 20  ,  x - 25  ,  y + 5   ,  c  ,  2.0f);
    al_draw_line(x - 25  ,  y + 5   ,  x - 25  ,  y - 10  ,  c  ,  2.0f);
    al_draw_line(x - 25  ,  y - 10  ,  x - 5   ,  y - 10  ,  c  ,  2.0f);
    al_draw_line(x - 5   ,  y - 10  ,  x - 10  ,  y - 20  ,  c  ,  2.0f);
    al_draw_line(x - 10  ,  y - 20  ,  x + 5   ,  y - 20  ,  c  ,  2.0f);
    al_draw_line(x + 5   ,  y - 20  ,  x + 20  ,  y - 10  ,  c  ,  2.0f);
    al_draw_line(x + 20  ,  y - 10  ,  x + 20  ,  y - 5   ,  c  ,  2.0f);
    al_draw_line(x + 20  ,  y - 5   ,  x + 0   ,  y + 0   ,  c  ,  2.0f);
    al_draw_line(x + 0   ,  y + 0   ,  x + 20  ,  y + 10  ,  c  ,  2.0f);
    al_draw_line(x + 20  ,  y + 10  ,  x + 10  ,  y + 20  ,  c  ,  2.0f);
    al_draw_line(x + 10  ,  y + 20  ,  x + 0   ,  y + 15  ,  c  ,  2.0f);
    al_draw_line(x + 0   ,  y + 15  ,  x - 20  ,  y + 20  ,  c  ,  2.0f);
}

void Asteroid_setPoition(Asteroid *a, int x, int y)
{
    a->motion.x = x;
    a->motion.y = y;
}

void Asteroid_move(Asteroid *a)
{
    a->motion.y += a->motion.speed;
}

void Asteroid_destroy(Asteroid *a)
{
    //free(a->color);
    //free(a->motion);
    free(a);
}


