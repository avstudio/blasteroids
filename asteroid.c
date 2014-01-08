#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "asteroid.h"

void drawAsteroid(Asteroid *a)
{
    int x           = a->x;
    int y           = a->y;
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

void moveAsteroidDown(Asteroid *a)
{
    a->y += a->speed;
}
