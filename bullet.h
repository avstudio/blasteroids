#ifndef _bullet_h
#define _bullet_h

#include "global.h"

typedef struct
{
  bool live;
  Motion motion;
} Bullet;

void Bullet_init(Bullet *b);
void Bullet_draw(Bullet *b);
#endif