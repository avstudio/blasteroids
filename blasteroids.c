#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "player.h"
#include "asteroid.h"

//GLOBALS==============================
const int WIDTH           = 800;
const int HEIGHT          = 400;
const int FPS             = 60;
const int ASTEROIDS_COUNT = 5;
ALLEGRO_DISPLAY *display  = NULL;
ALLEGRO_TRANSFORM t;

enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};
Asteroid asteroids[5];

void initPlayer(Player *player);
void initAsteroid(Asteroid *asteroid);
void moveAsteroids(void);
void resetAsteroidPos(Asteroid *asteroid);


int main(int argc, char **argv)
{
    srand(time(NULL));
    //object variables
    Player player;
    //primitive variable
    bool done                        = false;
    bool redraw                      = true;
    int i                            = 0;

    //Allegro variables
    ALLEGRO_DISPLAY *display         = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer             = NULL;
    ALLEGRO_FONT *font18             = NULL;

    //Initialization Functions
    if (!al_init()) //initialize Allegro
        return -1;
    //Allegro Module Init
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();

    al_identity_transform(&t);


    display = al_create_display(WIDTH, HEIGHT); //create our display object
    if (!display) //test display object
        return -1;

    event_queue = al_create_event_queue();
    timer       = al_create_timer(1.0 / FPS);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    //Game Init
    initPlayer(&player);
    for (i = 0; i < ASTEROIDS_COUNT; ++i)
    {
        asteroids[i].ID = i;
        initAsteroid(&asteroids[i]);
    }


    al_start_timer(timer);



    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            if (keys[RIGHT])
                movePlayerRight(&player);
            if (keys[LEFT])
                movePlayerLeft(&player);
            if (keys[UP])
                movePlayerUp(&player);
            if (keys[DOWN])
                movePlayerDown(&player);
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                break;
            }
        }

        // Draw stuff to screen
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            drawPlayer(&player);
            for (i = 0; i < ASTEROIDS_COUNT; ++i)
                drawAsteroid(&asteroids[i]);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            moveAsteroids();
        }
    }
    return 0;
}

void moveAsteroids()
{
    int i;
    for (i = 0; i < ASTEROIDS_COUNT; ++i)
    {
        if (asteroids[i].y > HEIGHT + 100)
            resetAsteroidPos(&asteroids[i]);
        moveAsteroidDown(&asteroids[i]);
    }
}

void resetAsteroidPos(Asteroid *a)
{
    a->y = - (rand() % 200);
    a->x = rand() % WIDTH;
}

void initAsteroid(Asteroid *a)
{
    int rx   =  rand() % WIDTH;
    int rs   =  (rand() % 5) + 1;
    a->x     = rx;
    a->y     = 100;
    a->speed = rs;
    a->angle = 38;
    a->color = al_map_rgb(3, 173, 49);
    // set_transform_for_asteroid(&t,a);

}


void initPlayer(Player *p)
{
    p->x      = WIDTH / 2;
    p->y      = HEIGHT / 2;
    p->height = 40;
    p->width  = 40;
    p->speed  = 3;
    p->color  = al_map_rgb(3, 173, 49);
}

