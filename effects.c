#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "effects.h"

void Explosion_init(Explosion *e,  ALLEGRO_BITMAP *image)
{
    e->live                   = false;

    e->motion.speed           = (rand() % 4) + 1;
    e->motion.x               = 100;
    e->motion.y               = 100;

    e->animation.direction    = 1;
    e->animation.maxFrame     = 24;
    e->animation.curFrame     = 0;
    e->animation.frameCount   = 0;
    e->animation.frameDelay   = 4;
    e->animation.frameWidth   = 64;
    e->animation.frameHeight  = 64;
    e->animation.numOfColumns = 5;
    e->animation.numOfRows    = 5;
    e->animation.image        = image;
}

void Explosion_draw(Explosion *e)
{
    if (e->live)
    {

        if (++e->animation.frameCount >= e->animation.frameDelay)
        {
            e->animation.curFrame += 1;
            if (e->animation.curFrame >= e->animation.maxFrame)
            {
                e->animation.curFrame = e->animation.maxFrame ;
                e->live = false;
            }
            e->animation.frameCount = 0;
        }
        int fx = (e->animation.curFrame % e->animation.numOfColumns) * e->animation.frameWidth;
        int fy = (e->animation.curFrame / e->animation.numOfColumns) * e->animation.frameHeight;
        al_draw_bitmap_region(e->animation.image, fx, fy, e->animation.frameWidth,
                              e->animation.frameHeight, e->motion.x - e->animation.frameWidth / 2, e->motion.y - e->animation.frameHeight / 2, 0);
    }
}

void Explosion_reset(Explosion *e, int x , int y)
{
    e->animation.curFrame   = 0;
    e->animation.frameCount = 0;
    e->motion.x             = x;
    e->motion.y             = y;
    e->live                 = true;
}


void Explosion_destroy(Explosion *e)
{
    //free(e->color);
    //free(e->motion);
    free(e);
}

