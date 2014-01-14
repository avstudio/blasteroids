#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "player.h"
#include "enemy.h"
#include "effects.h"
#include "bullet.h"
#include "global.h"

#define  BG_IMAGE                "images/11750.jpg"
#define  PLAYER_IMAGE            "images/ship.png"
#define  EXPLOSION_IMAGE         "images/explosion.png"
#define  ENEMY_IMAGE             "images/asteroid@50.png"
#define  ASTEROID_DIE_SAMPLE     "sfx/hit3.wav"
#define  BULLET_FIRED_SAMPLE     "sfx/pewpew.wav"



//globals=========
const int WIDTH            = 800;
const int MAX_PLAYERS      = 3;
const int HEIGHT           = 600;
const int FRAME_MARGIN     = 30;
const int FPS              = 60;
const int ASTEROIDS_COUNT  = 5;
const int BULLETS_COUNT    = 5;
const int EXPLOSIONS_COUNT = 5;
int NUM_OF_PLAYERS   = 1;
enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};


//generic
void error(char *msg);
int  isCollision(Motion *m1, Motion *m2);

//enemy
void initEnemies(Enemy enemies[], int size, ALLEGRO_BITMAP *image);
void controllEnemies(Enemy enemies[], int size);
void drawEnemies(Enemy enemies[], int size);
void startEnemies(Enemy enemies[], int size);

//bullet
void initBullets(Bullet bullets[], int size);
void initExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP *explosionImage);
void controllBullets(Bullet bullets[], int size);
void fireBullet(Bullet bullets[], int size, Player *player, ALLEGRO_SAMPLE *bullet_fired_sample);
void drawBullets(Bullet bullets[], int size);

//explosion
void drawExplosions(Explosion explosions[], int size);
void startExpolsion(Explosion explosions[], int x, int y, int size);

//collision
void collideBulletsAndEnemies(Bullet bullets[], int bSize, Enemy enemies[], int aSize, Player *player, Explosion explosions[], int expSize, ALLEGRO_SAMPLE *sample);
void collideEnemiesAndPlayer(Enemy enemies[], int size, Player *player, Explosion explosions[], int expSize);



int main(int argc, char **argv)
{
    ALLEGRO_TRANSFORM t;
    ALLEGRO_DISPLAY *display            = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue    = NULL;
    ALLEGRO_TIMER *timer                = NULL;
    ALLEGRO_FONT *font13                = NULL;
    ALLEGRO_BITMAP *bgImage             = NULL;
    ALLEGRO_BITMAP *playerImage         = NULL;
    ALLEGRO_BITMAP *enemyImage          = NULL;
    ALLEGRO_BITMAP *explosionImage      = NULL;
    ALLEGRO_SAMPLE *asteroid_die_sample = NULL;
    ALLEGRO_SAMPLE *bullet_fired_sample = NULL;

    //objects
    Enemy enemies[ASTEROIDS_COUNT * NUM_OF_PLAYERS];
    Explosion explosions[EXPLOSIONS_COUNT * NUM_OF_PLAYERS];
    Bullet bullets[BULLETS_COUNT * NUM_OF_PLAYERS];
    Player players[NUM_OF_PLAYERS];
    Player *player = &players[0];//todo

    //other
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
    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(4);


    display = al_create_display(WIDTH, HEIGHT);
    if (!display)
        return -1;

    bgImage             = al_load_bitmap(BG_IMAGE);
    playerImage         = al_load_bitmap(PLAYER_IMAGE);
    explosionImage      = al_load_bitmap(EXPLOSION_IMAGE);
    enemyImage          = al_load_bitmap(ENEMY_IMAGE);
    event_queue         = al_create_event_queue();
    timer               = al_create_timer(1.0 / FPS);
    asteroid_die_sample = al_load_sample(ASTEROID_DIE_SAMPLE);
    bullet_fired_sample = al_load_sample(BULLET_FIRED_SAMPLE);

    al_convert_mask_to_alpha(playerImage, al_map_rgb(255, 0, 255));
    al_convert_mask_to_alpha(explosionImage, al_map_rgb(0, 0, 0));

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
    initEnemies(enemies, ASTEROIDS_COUNT, enemyImage);
    initBullets(bullets, BULLETS_COUNT);
    initExplosions(explosions, EXPLOSIONS_COUNT, explosionImage);

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
            if (keys[UP]    && player->motion.y > HEIGHT / 3)                  Player_move(player, NORTH);
            else if (keys[DOWN]  && player->motion.y < HEIGHT - FRAME_MARGIN ) Player_move(player, SOUTH);
            else if (keys[RIGHT] && player->motion.x < WIDTH  - FRAME_MARGIN)  Player_move(player, EAST);
            else if (keys[LEFT]  && player->motion.x > FRAME_MARGIN)           Player_move(player, WEST);
            else Player_reset(player);

            controllEnemies(enemies, ASTEROIDS_COUNT);
            controllBullets(bullets, BULLETS_COUNT);
            collideBulletsAndEnemies(bullets, BULLETS_COUNT, enemies, ASTEROIDS_COUNT, player, explosions, EXPLOSIONS_COUNT, asteroid_die_sample);
            collideEnemiesAndPlayer(enemies, ASTEROIDS_COUNT, player, explosions, EXPLOSIONS_COUNT);

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
                fireBullet(bullets, BULLETS_COUNT, player, bullet_fired_sample);
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
                drawEnemies(enemies, ASTEROIDS_COUNT);

                drawExplosions(explosions, EXPLOSIONS_COUNT);
                Player_draw(player);
                drawBullets(bullets, BULLETS_COUNT);
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
    //al_destroy_sample(sample);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(bgImage);
    al_destroy_bitmap(enemyImage);
    al_destroy_bitmap(playerImage);
    al_destroy_bitmap(explosionImage);
    return 0;
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

void initEnemies(Enemy enemies[], int size , ALLEGRO_BITMAP *image)
{
    for (int i = 0; i < size; i++)
    {
        enemies[i].ID = i;
        Enemy_init(&enemies[i], rand() % WIDTH, -(rand() % 120), image);
    }
}

void initExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP *explosionImage)
{
    for (int i = 0; i < size; ++i)
    {
        Explosion_init(&explosions[i], explosionImage);
    }
}

void drawExplosions(Explosion explosions[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (explosions[i].live)
            Explosion_draw(&explosions[i]);
    }
}

void controllEnemies(Enemy enemies[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (enemies[i].live)
        {

            enemies[i].motion.y += enemies[i].motion.speed;
        }
        else
        {
            enemies[i].live     = true;
            enemies[i].motion.x = 30 + rand() % (WIDTH - 60);
            enemies[i].motion.y = - 100;
        }
        if (enemies[i].motion.y > HEIGHT + 100)
            enemies[i].live     = false;//send event
    }
}

void drawEnemies(Enemy enemies[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (enemies[i].live)
            Enemy_draw(&enemies[i]);
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

void collideBulletsAndEnemies(Bullet bullets[], int bSize, Enemy enemies[], int aSize, Player *player, Explosion explosions[], int expSize, ALLEGRO_SAMPLE *sample)
{
    for (int i = 0; i < bSize; i++)
    {
        if (bullets[i].live)
        {
            for (int j = 0; j < aSize; j++)
            {
                if (enemies[j].live)
                {
                    if (isCollision(&bullets[i].motion, &enemies[j].motion))
                    {
                        bullets[i].live   = false;
                        enemies[j].live = false;
                        player->score ++;
                        startExpolsion(explosions, bullets[i].motion.x, bullets[i].motion.y, expSize);
                        //al_stop_sample(sample);
                        al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                }
            }
        }
    }
}

void startExpolsion(Explosion explosions[], int x, int y, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (!explosions[i].live)
        {
            Explosion_reset(&explosions[i], x , y);
            break;
        }

    }
}

void collideEnemiesAndPlayer(Enemy enemies[], int size, Player *player, Explosion explosions[], int expSize)
{
    for (int i = 0; i < size; i++)
    {
        if (enemies[i].live)
        {
            if (isCollision(&enemies[i].motion, &player->motion))
            {
                enemies[i].live = false;
                player->energy -= player->energy_step;
            }
        }
    }
}

void fireBullet(Bullet bullets[], int size, Player *player, ALLEGRO_SAMPLE *bullet_fired_sample)
{
    for ( int i = 0; i < size; i++)
    {
        if (!bullets[i].live)
        {
            bullets[i].motion.x = player->motion.x ;
            bullets[i].motion.y = player->motion.y - 17;
            bullets[i].live = true;
            al_play_sample(bullet_fired_sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            break;
        }
    }
}



