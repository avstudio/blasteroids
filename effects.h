#ifndef _effects_h
#define _effects_h

#include "effects.h"
#include "global.h"

typedef struct
{
    int live;
    Motion motion;
    Animation animation;
} Explosion;

void Explosion_init(Explosion *e, ALLEGRO_BITMAP *image);
void Explosion_destroy(Explosion *e);
void Explosion_start(Explosion *e);
#endif