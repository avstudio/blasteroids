#ifndef _asteroid_h
#define _asteroid_h

#include "global.h"

typedef struct
{
    int ID;
    int live;
    ALLEGRO_COLOR color;
    Motion motion;
} Asteroid;


void Asteroid_init(Asteroid *a, int, int);
void Asteroid_draw(Asteroid *self);
void Asteroid_move(Asteroid *self);
void Asteroid_setPoition(Asteroid *self, int, int);
#endif
