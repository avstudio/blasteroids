#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "global.h"



//globals=========
const int WIDTH           = 800;
const int MAX_PLAYERS     = 800;
const int HEIGHT          = 600;
const int FRAME_MARGIN    = 30;
const int FPS             = 60;
const int ASTEROIDS_COUNT = 5;
const int BULLETS_COUNT   = 5;
enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};



void error(char *msg);
void drawFrame(Player *player, Player *playerLifes);
void initEnemys(Enemy enemys[], int size, ALLEGRO_BITMAP *image);
void controllEnemys(Enemy enemys[], int size);
void drawEnemys(Enemy enemys[], int size);
void initBullets(Bullet bullets[], int size);
void fireBullet(Bullet bullets[], int size, Player *player);
void drawBullets(Bullet bullets[], int size);
void controllBullets(Bullet bullets[], int size);
void startEnemys(Enemy enemys[], int size);
int  isCollision(Motion *m1, Motion *m2);
void collideBulletsAndEnemys(Bullet bullets[], int bSize, Enemy enemys[], int aSize, Player *player);
void collideEnemysAndPlayer(Enemy enemys[], int size, Player *player);

int main(int argc, char **argv)
{
    ALLEGRO_TRANSFORM t;
    ALLEGRO_DISPLAY *display         = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer             = NULL;
    ALLEGRO_FONT *font13             = NULL;
    ALLEGRO_BITMAP *bgImage          = NULL;
    ALLEGRO_BITMAP *playerImage      = NULL;
    ALLEGRO_BITMAP *enemyImage    = NULL;


    Enemy enemys[ASTEROIDS_COUNT];
    Bullet bullets[BULLETS_COUNT];
    Player players[3];
    Player *player = &players[0];
    Player playerLifes[2];


    bool done       = false;
    bool isGameOver = false;
    bool redraw     = true;
    bool keys[5]    = {false, false, false, false, false};
    int i           = 0;

    if (!al_init())
        error("Error with game initialization!");

    al_init_primitives_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    display = al_create_display(WIDTH, HEIGHT);
    if (!display)
        return -1;

    bgImage       = al_load_bitmap("11750.jpg");
    playerImage   = al_load_bitmap("ship.png");
    al_convert_mask_to_alpha(playerImage, al_map_rgb(255, 0, 255));
    enemyImage = al_load_bitmap("asteroid@50.png");

    event_queue   = al_create_event_queue();
    timer         = al_create_timer(1.0 / FPS);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    srand(time(NULL));

    font13 = al_load_ttf_font("pirulen.ttf", 13, 0 );
    if (!font13)
        error("Could not load 'pirulen.ttf'.\n");

    //init game objects============================================
    //

    Player_init(player, WIDTH / 2 - 12, HEIGHT  - 20, playerImage);
    initEnemys(enemys, ASTEROIDS_COUNT, enemyImage);
    initBullets(bullets, BULLETS_COUNT);

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
            if (keys[UP]    && player->motion.y > HEIGHT/3)     Player_move(player, NORTH);
            else if (keys[DOWN]  && player->motion.y < HEIGHT ) Player_move(player, SOUTH);
            else if (keys[RIGHT] && player->motion.x < WIDTH )  Player_move(player, EAST);
            else if (keys[LEFT]  && player->motion.x > 0)       Player_move(player, WEST);
            else Player_reset(player);


            controllEnemys(enemys, ASTEROIDS_COUNT);
            controllBullets(bullets, BULLETS_COUNT);
            collideBulletsAndEnemys(bullets, BULLETS_COUNT, enemys, ASTEROIDS_COUNT, player);
            collideEnemysAndPlayer(enemys, ASTEROIDS_COUNT, player);

            if (player->energy <= 0)
                isGameOver = true;
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
                fireBullet(bullets, BULLETS_COUNT, player);
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
            if (!isGameOver)
            {
                al_draw_bitmap(bgImage, -100 , -100, 0);
                drawEnemys(enemys, ASTEROIDS_COUNT);
                Player_draw(player);

                drawBullets(bullets, BULLETS_COUNT);
                drawFrame(player, playerLifes);
                al_draw_textf(font13, al_map_rgb(255, 0, 255), 5, 5, 0, "%d lives left. Destroyed %d objects", player->energy, player->score);
            }
            else
            {
                al_draw_textf(font13, al_map_rgb(0, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %d", player->score);
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }
    //destroy things
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(bgImage);
    al_destroy_bitmap(enemyImage);
    al_destroy_bitmap(playerImage);
    return 0;
}

void drawFrame(Player *player, Player *playerLifes )
{
    for (int i = 0; i <  player->energy - 1; ++i)
    {
        playerLifes[i].motion.x = 40  + ( i * 40);
        playerLifes[i].motion.y = 50;
        //Player_draw(&playerLifes[i],playerImage);
        // al_draw_bitmap_region( playerImage, fx, fy, player->frameWidth,
        //                   player->frameHeight, player->motion.x - player->frameWidth / 2, player->motion.y - player->frameHeight / 2, 0);



    }
}

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void initBullets(Bullet bullets[], int size)
{
    for (int i = 0; i < size; i++)
        Bullet_init(&bullets[i]);
}

void initEnemys(Enemy enemys[], int size , ALLEGRO_BITMAP *image)
{
    for (int i = 0; i < size; i++)
    {
        enemys[i].ID = i;
        Enemy_init(&enemys[i], rand() % WIDTH, -(rand() % 120), image);
    }
}

void controllEnemys(Enemy enemys[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (enemys[i].live)
        {

            enemys[i].motion.y += enemys[i].motion.speed;
        }
        else
        {
            enemys[i].live     = true;
            enemys[i].motion.x = 30 + rand() % (WIDTH - 60);
            enemys[i].motion.y = - 100;
        }
        if (enemys[i].motion.y > HEIGHT + 100)
            enemys[i].live     = false;//send event
    }
}

void drawEnemys(Enemy enemys[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (enemys[i].live)
            Enemy_draw(&enemys[i]);
    }
}
void drawBullets(Bullet bullets[], int size)
{
    for ( int i = 0; i < size; i++)
        if (bullets[i].live)
            Bullet_draw(&bullets[i]);
}

void controllBullets(Bullet bullets[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (bullets[i].live)
        {
            bullets[i].motion.y -= bullets[i].motion.speed;
            if (bullets[i].motion.y < 0)
                bullets[i].live = false;
        }
    }
}


int isCollision(Motion *m1, Motion *m2)
{
    if (m1->x - m1->bx < m2->x + m2->bx &&
            m1->x + m1->bx > m2->x - m2->bx &&
            m1->y - m1->by < m2->y + m2->by &&
            m1->y + m1->by > m2->y - m2->by)
        return 1;
    return 0;
}

void collideBulletsAndEnemys(Bullet bullets[], int bSize, Enemy enemys[], int aSize, Player *player)
{
    for (int i = 0; i < bSize; i++)
    {
        if (bullets[i].live)
        {
            for (int j = 0; j < aSize; j++)
            {
                if (enemys[j].live)
                {
                    if (isCollision(&bullets[i].motion, &enemys[j].motion))
                    {
                        bullets[i].live   = false;
                        enemys[j].live = false;
                        player->score ++;
                    }
                }
            }
        }
    }
}

void collideEnemysAndPlayer(Enemy enemys[], int size, Player *player)
{
    for (int i = 0; i < size; i++)
    {
        if (enemys[i].live)
        {
            if (isCollision(&enemys[i].motion, &player->motion))
            {
                enemys[i].live = false;
                player->energy -= player->energy_step;
            }
        }
    }
}

void fireBullet(Bullet bullets[], int size, Player *player)
{
    for ( int i = 0; i < size; i++)
    {
        if (!bullets[i].live)
        {
            bullets[i].motion.x = player->motion.x ;
            bullets[i].motion.y = player->motion.y - 17;
            bullets[i].live = true;
            break;
        }
    }
}



