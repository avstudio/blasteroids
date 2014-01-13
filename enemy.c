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

    e->maxFrame = 60;
    e->curFrame = 0;
    e->frameCount = 0;
    e->frameDelay = 1;
    e->frameWidth = 64;
    e->frameHeight = 64;
    e->animationColumns = 8;


    if (rand() % 2)
        e->animationDirection = 1;
    else
        e->animationDirection = -1;

    e->animationRow = 8;

    e->image = image;
}





void Enemy_draw(Enemy *e)
{
    updateAnimation(e);
    int fx = (e->curFrame % e->animationColumns) * e->frameWidth;
    int fy = (e->curFrame / e->animationColumns) * e->frameHeight;
    al_draw_bitmap_region(e->image, fx, fy, e->frameWidth,
                          e->frameHeight, e->motion.x - e->frameWidth / 2, e->motion.y - e->frameHeight / 2, 0);

    // al_draw_filled_rectangle(e->motion.x - e->motion.bx, e->motion.y - e->motion.by, e->motion.x + e->motion.bx,
    //                          e->motion.y + e->motion.by, al_map_rgba(255, 0, 255, 100));


    // al_draw_line(x - 20  ,  y + 20  ,  x - 25  ,  y + 5   ,  c  ,  2.0f);
    // al_draw_line(x - 25  ,  y + 5   ,  x - 25  ,  y - 10  ,  c  ,  2.0f);
    // al_draw_line(x - 25  ,  y - 10  ,  x - 5   ,  y - 10  ,  c  ,  2.0f);
    // al_draw_line(x - 5   ,  y - 10  ,  x - 10  ,  y - 20  ,  c  ,  2.0f);
    // al_draw_line(x - 10  ,  y - 20  ,  x + 5   ,  y - 20  ,  c  ,  2.0f);
    // al_draw_line(x + 5   ,  y - 20  ,  x + 20  ,  y - 10  ,  c  ,  2.0f);
    // al_draw_line(x + 20  ,  y - 10  ,  x + 20  ,  y - 5   ,  c  ,  2.0f);
    // al_draw_line(x + 20  ,  y - 5   ,  x + 0   ,  y + 0   ,  c  ,  2.0f);
    // al_draw_line(x + 0   ,  y + 0   ,  x + 20  ,  y + 10  ,  c  ,  2.0f);
    // al_draw_line(x + 20  ,  y + 10  ,  x + 10  ,  y + 20  ,  c  ,  2.0f);
    // al_draw_line(x + 10  ,  y + 20  ,  x + 0   ,  y + 15  ,  c  ,  2.0f);
    // al_draw_line(x + 0   ,  y + 15  ,  x - 20  ,  y + 20  ,  c  ,  2.0f);
    //

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
    if (++e->frameCount >= e->frameDelay)

    {
        e->curFrame += e->animationDirection;
        if (e->curFrame >= e->maxFrame)
            e->curFrame = 0;
        else if ( e->curFrame <= 0)
            e->curFrame = e->maxFrame - 1;

        e->frameCount = 0;
    }
}


