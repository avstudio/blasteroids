#ifndef _global_h
#define _global_h

typedef struct
{
    int x;
    int bx;
    int y;
    int by;
    int speed;
    int anlge;
} Motion;

typedef struct
{
    int maxFrame;
    int curFrame;
    int curRow;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int direction;
    int numOfColumns;
    int numOfRows;
    ALLEGRO_BITMAP *image;

} Animation;

typedef union ALLEGRO_EVENT ALLEGRO_EVENT;
#endif

