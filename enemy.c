#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "enemy.h"

void Enemy_init(Enemy *e, int x, int y, ALLEGRO_BITMAP *image)
{
    e->color = al_map_rgb(3, 173, 49);
    e->live  = false;

    e->motion.speed = (rand() % 4) + 1;
    e->motion.x  = x;
    e->motion.y  = y;
    e->motion.bx = 18;
    e->motion.by = 18;

    e->animation.maxFrame = 60;
    e->animation.curFrame = 0;
    e->animation.frameCount = 0;
    e->animation.frameDelay = 1;
    e->animation.frameWidth = 64;
    e->animation.frameHeight = 64;
    e->animation.numOfColumns = 8;


    if (rand() % 2)
        e->animation.direction = 1;
    else
        e->animation.direction = -1;

    e->animation.numOfRows = 8;

    e->animation.image = image;
}

void Enemy_draw(Enemy *e)
{
    updateAnimation(e);
    int fx = (e->animation.curFrame % e->animation.numOfColumns) * e->animation.frameWidth;
    int fy = (e->animation.curFrame / e->animation.numOfColumns) * e->animation.frameHeight;
    al_draw_bitmap_region(e->animation.image, fx, fy, e->animation.frameWidth,
                          e->animation.frameHeight, e->motion.x - e->animation.frameWidth / 2, e->motion.y - e->animation.frameHeight / 2, 0);

    // al_draw_filled_rectangle(e->motion.x - e->motion.bx, e->motion.y - e->motion.by, e->motion.x + e->motion.bx,
    //                          e->motion.y + e->motion.by, al_map_rgba(255, 0, 255, 100));
}

void Enemy_move(Enemy *e)
{
    e->motion.y += e->motion.speed;
}

void Enemy_destroy(Enemy *e)
{
    //free(e->color);
    //free(e->motion);
    free(e);
}
//private

void updateAnimation(Enemy *e)
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


