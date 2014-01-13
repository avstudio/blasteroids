#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "player.h"

void Player_init(Player *p, int x, int y, ALLEGRO_BITMAP *image)
{
    p->energy             = 3;
    p->energy_step        = 1;
    p->score              = 0;
    p->height             = 40;
    p->width              = 40;
    p->color              = al_map_rgb(3, 173, 49);

    p->motion.speed       = 10;
    p->motion.x           = x;
    p->motion.y           = y;
    p->motion.bx          = 12;
    p->motion.by          = 12;


    p->maxFrame           = 3;
    p->curFrame           = 1;
    p->frameCount         = 0;
    p->frameWidth         = 47;
    p->frameHeight        = 41;
    p->animationColumns   = 3;
    p->animationDirection = 1;

    p->animationRow       = 1;
    p->image              = image;

}
void Player_SetAnimation(Player *p, int position)
{
    if (position == 1)
        p->animationRow = 1;
    else
        p->curFrame = 0;
}
void Player_destroy(Player *p)
{
    //free(p->color);
    //free(p->motion);
    free(p);
}

void Player_draw(Player *player)
{

    int fx = (player->curFrame % player->animationColumns) * player->frameWidth;
    int fy = player->animationRow * player->frameHeight;
    al_draw_bitmap_region( player->image, fx -7, fy, player->frameWidth,
                           player->frameHeight, player->motion.x - player->frameWidth / 2, player->motion.y - player->frameHeight / 2, 0);


    // al_draw_filled_rectangle(player->motion.x - player->motion.bx, player->motion.y - player->motion.by, player->motion.x + player->motion.bx,
    //     player->motion.y + player->motion.by, al_map_rgba(255, 0, 255, 100));
}

void Player_reset(Player *p)
{
    p->animationRow = 1;
    p->curFrame = 1;
}

void Player_move(Player *p, Direction direction)
{
    p->curFrame = 1;
    switch (direction)
    {
    case NORTH:
        p->motion.y -= p->motion.speed;
        p->animationRow = 0;
        break;
    case SOUTH:
        p->motion.y += p->motion.speed;
        p->animationRow = 2;
        break;
    case WEST:
        p->motion.x -= p->motion.speed;
        p->curFrame = 0;
        break;
    case EAST:
        p->motion.x += p->motion.speed;
        p->curFrame = 2;
        break;
    }
}
