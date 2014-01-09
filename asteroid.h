#include <allegro5/allegro.h>

typedef struct
{
    int ID;
    float x;
    float y;
    float sx;
    float sy;
    float heading;
    float twist;
    float rotation;
    float speed;
    float angle;
    float rot_velocity;
    float scale;
    int gone;
    ALLEGRO_COLOR color;
} Asteroid;

void drawAsteroid(Asteroid *asteroid);
void moveAsteroidDown(Asteroid *asteroid);
void initAsteroid(Asteroid *a);
