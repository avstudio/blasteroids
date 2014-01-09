#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "asteroid.h"

void drawAsteroid(Asteroid *a)
{
    int x           = a->x;
    int y           = a->y;
    ALLEGRO_COLOR c = a->color;
    //ALLEGRO_TRANSFORM transform, old;
    //set_transform_for_asteroid(&transform , a);
    //al_use_transform(&transform);
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

// void draw_ship(SHIP *s)
// {
//     ALLEGRO_TRANSFORM transform, old;
//     set_transform_for_ship(&transform , s);
//     // follow our camera
//     al_translate_transform(&transform , -camera_xpos , -camera_ypos);
//     al_use_transform(&transform);
//     al_draw_filled_rectangle(s->x , s->y , s->rx , s->by , al_map_rgb(255, 127, 0));
//     // theoretically, reset transformation matrix for allegro here,too lazy though
// }

void moveAsteroidDown(Asteroid *a)
{
    a->y += a->speed;
}

void set_transform_for_asteroid(ALLEGRO_TRANSFORM *t , Asteroid *a)
{
    al_identity_transform(t);
    // center on ship
    al_translate_transform(t , -40 , -40);
    // rotate
    al_rotate_transform(t , a->angle);
    // move ship back where it was
    al_translate_transform(t , 40 , 40);
}


