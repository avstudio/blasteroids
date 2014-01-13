#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "effects.h"

void Explosion_init(Explosion *e,  ALLEGRO_BITMAP *image)
{
    e->live                   = false;

    e->motion.speed           = (rand() % 4) + 1;
    e->motion.x               = 0;
    e->motion.y               = 0;
    e->motion.bx              = 18;
    e->motion.by              = 18;

    e->animation.maxFrame     = 16;
    e->animation.curFrame     = 0;
    e->animation.frameCount   = 0;
    e->animation.frameDelay   = 4;
    e->animation.frameWidth   = 128;
    e->animation.frameHeight  = 128;
    e->animation.numOfColumns = 4;
    e->animation.direction    = 1;
    e->animation.numOfRows    = 4;
    e->animation.image        = image;
}

void Explosion_start(Explosion *e)
{
    if (++e->animation.frameCount >= e->animation.frameDelay)
    {
        e->animation.curFrame += e->animation.direction;
        if (e->animation.curFrame >= e->animation.maxFrame)
            e->animation.curFrame = 0;
        else if ( e->animation.curFrame <= 0)
            e->animation.curFrame = e->animation.maxFrame - 1;
        e->animation.frameCount = 0;
    }
}


void Explosion_destroy(Explosion *e)
{
    //free(e->color);
    //free(e->motion);
    free(e);
}