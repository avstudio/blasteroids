#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "player.h"

void Player_init(Player *p, int x, int y)
{
    p->energy       = 3;
    p->energy_step  = 1;
    p->height       = 40;
    p->width        = 40;
    p->color        = al_map_rgb(3, 173, 49);

    p->motion.speed = 10;
    p->motion.x     = x;
    p->motion.y     = y;
    p->motion.bx    = 7;
    p->motion.by    = 7;
}

void Player_destroy(Player *p)
{
    //free(p->color);
    //free(p->motion);
    free(p);
}

void Player_draw(Player *p)
{
    al_draw_filled_rectangle(p->motion.x - 9, p->motion.y , p->motion.x - 7, p->motion.y - 22, al_map_rgb(255, 0, 0));
    al_draw_filled_rectangle(p->motion.x + 7, p->motion.y , p->motion.x + 9, p->motion.y - 22, al_map_rgb(255, 0, 0));
    al_draw_filled_triangle( p->motion.x - 16,p->motion.y , p->motion.x    , p->motion.y - 22, p->motion.x + 16, p->motion.y, al_map_rgb(0, 255, 0));
    al_draw_filled_rectangle(p->motion.x - 2, p->motion.y , p->motion.x + 2, p->motion.y - 22, al_map_rgb(0, 0, 255));
}

void Player_move(Player *p, Direction direction)
{
    switch (direction)
    {
    case NORTH:
        p->motion.y -= p->motion.speed;
        break;
    case SOUTH:
        p->motion.y += p->motion.speed;
        break;
    case WEST:
        p->motion.x -= p->motion.speed;
        break;
    case EAST:
        p->motion.x += p->motion.speed;
        break;
    }
}
