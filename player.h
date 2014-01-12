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
    int energy_step;
    ALLEGRO_COLOR color;
    Motion motion;
} Player;


void Player_init(Player *p,int, int);
void Player_draw(Player *self);
void Player_move(Player *self, Direction direction);
void Player_destroy(Player *p);

#endif