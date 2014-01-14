#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "player.h"

void Player_init(Player *p, int x, int y, ALLEGRO_BITMAP *image)
{
    p->energy                 = 3;
    p->energy_step            = 1;
    p->score                  = 0;
    p->height                 = 40;
    p->width                  = 40;
    p->color                  = al_map_rgb(3, 173, 49);

    p->motion.speed           = 10;
    p->motion.x               = x;
    p->motion.y               = y;
    p->motion.bx              = 12;
    p->motion.by              = 12;

    p->animation.maxFrame     = 3;
    p->animation.curFrame     = 1;
    p->animation.frameCount   = 0;
    p->animation.frameWidth   = 47;
    p->animation.frameHeight  = 41;
    p->animation.numOfColumns = 3;
    p->animation.direction    = 1;
    p->animation.curRow       = 1;
    p->animation.image        = image;
}
int Player_isDead(Player *p)
{
    return p->energy == 0;
}
void Player_destroy(Player *p)
{
    //free(p->color);
    //free(p->motion);
    free(p);
}

void Player_draw(Player *p)
{

    int fx = (p->animation.curFrame % p->animation.numOfColumns) * p->animation.frameWidth;
    int fy = p->animation.curRow * p->animation.frameHeight;
    al_draw_bitmap_region( p->animation.image, fx - 7, fy, p->animation.frameWidth,
                           p->animation.frameHeight, p->motion.x - p->animation.frameWidth / 2, p->motion.y - p->animation.frameHeight / 2, 0);


    // al_draw_filled_rectangle(p->motion.x - p->motion.bx, p->motion.y - p->motion.by, p->motion.x + p->motion.bx,
    //     player->motion.y + player->motion.by, al_map_rgba(255, 0, 255, 100));
}

void Player_reset(Player *p)
{
    p->animation.curRow = 1;
    p->animation.curFrame = 1;
}

void Player_move(Player *p, Direction direction)
{
    p->animation.curFrame = 1;
    switch (direction)
    {
    case NORTH:
        p->motion.y -= p->motion.speed;
        p->animation.curRow = 0;
        break;
    case SOUTH:
        p->motion.y += p->motion.speed;
        p->animation.curRow = 2;
        break;
    case WEST:
        p->motion.x -= p->motion.speed;
        p->animation.curFrame = 0;
        break;
    case EAST:
        p->motion.x += p->motion.speed;
        p->animation.curFrame = 2;
        break;
    }
}
