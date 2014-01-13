#ifndef _effects_h
#define _effects_h

#include "effects.h"
#include "global.h"

typedef struct
{
    ALLEGRO_BITMAP *image;



    Motion motion;
} Explosion;


void Player_init(Player *p, int, int, ALLEGRO_BITMAP *image);
void Player_reset(Player *p);
void Player_draw(Player *p);
void Player_move(Player *p, Direction direction);
void Player_destroy(Player *p);

#endif