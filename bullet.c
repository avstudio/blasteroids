#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "bullet.h"

void Bullet_init(Bullet *bullet)
{
    bullet->motion.speed = 10;
    bullet->live  = false;
    bullet->motion.bx = 2;
    bullet->motion.by = 2;
}

void Bullet_draw(Bullet *bullet)
{
    al_draw_filled_circle(bullet->motion.x, bullet->motion.y, 2, al_map_rgb(255, 255, 255));
}

void Bullet_destroy(Bullet *b)
{
    //free(a->color);
    //free(b->motion);
    free(b);
}
