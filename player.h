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
    ALLEGRO_COLOR color;
    Motion motion;
} Player;


Player *Player_create(int, int);
void Player_draw(Player *self);
void Player_move(Player *self, Direction direction);
void Player_destroy(Player *p);

#endif