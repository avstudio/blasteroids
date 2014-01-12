#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "player.h"


Player *Player_create(int x, int y)
{
    Player *p       = malloc(sizeof(Player));
    p->height       = 40;
    p->width        = 40;
    p->color        = al_map_rgb(3, 173, 49);

    p->motion.speed = 10;
    p->motion.x     = x;
    p->motion.y     = y;
    p->motion.bx    = 7;
    p->motion.by    = 7;
    return p;
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
