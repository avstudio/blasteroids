#ifndef _player_h
#define _player_h

#include "player.h"
#include "global.h"
typedef enum
{
    NORTH, SOUTH, WEST, EAST
} Direction;

typedef struct
{
    int ID;
    int height;
    int width;
    int energy;
    int score;
    int energy_step;
    ALLEGRO_COLOR color;

    ALLEGRO_BITMAP *image;

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationDirection;

    int animationRow;

    Motion motion;
} Player;


void Player_init(Player *p, int, int, ALLEGRO_BITMAP *image);
void Player_reset(Player *p);
void Player_draw(Player *p);
void Player_move(Player *p, Direction direction);
void Player_destroy(Player *p);

#endif