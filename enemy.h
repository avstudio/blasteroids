#ifndef _enemy_h
#define _enemy_h

#include "global.h"

typedef struct
{
    int ID;
    int live;
    ALLEGRO_COLOR color;
    Motion motion;

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationDirection;

    int animationRow;

    ALLEGRO_BITMAP *image;

} Enemy;


void Enemy_init(Enemy *e, int, int, ALLEGRO_BITMAP *image);
void Enemy_draw(Enemy *e);
void Enemy_move(Enemy *e);

void updateAnimation(Enemy *e);
#endif
