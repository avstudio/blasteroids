#ifndef _enemy_h
#define _enemy_h

#include "global.h"

typedef struct
{
    int ID;
    int live;
    ALLEGRO_COLOR color;
    Motion motion;
    Animation animation;
} Enemy;


void Enemy_init(Enemy *e, int, int, ALLEGRO_BITMAP *image);
void Enemy_draw(Enemy *e);
void Enemy_move(Enemy *e);

static void updateAnimation(Enemy *e);
#endif
