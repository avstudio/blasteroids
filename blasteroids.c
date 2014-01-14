#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "player.h"
#include "enemy.h"
#include "effects.h"
#include "bullet.h"
#include "global.h"



//globals=========
const int WIDTH            = 800;
const int MAX_PLAYERS      = 800;
const int HEIGHT           = 600;
const int FRAME_MARGIN     = 30;
const int FPS              = 60;
const int ASTEROIDS_COUNT  = 5;
const int BULLETS_COUNT    = 5;
const int EXPLOSIONS_COUNT = 5;
const int NUM_OF_PLAYERS   = 3;
enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};



void error(char *msg);
void drawFrame(Player *player, Player *playerLifes);
void initEnemies(Enemy enemies[], int size, ALLEGRO_BITMAP *image);
void controllEnemies(Enemy enemies[], int size);
void drawEnemies(Enemy enemies[], int size);
void initBullets(Bullet bullets[], int size);
void initExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP *explosionImage);
void drawExplosions(Explosion explosions[], int size);
void fireBullet(Bullet bullets[], int size, Player *player);
void drawBullets(Bullet bullets[], int size);
void controllBullets(Bullet bullets[], int size);
void startEnemies(Enemy enemies[], int size);
int  isCollision(Motion *m1, Motion *m2);
void collideBulletsAndEnemies(Bullet bullets[], int bSize, Enemy enemies[], int aSize, Player *player, Explosion explosions[], int expSize);
void collideEnemiesAndPlayer(Enemy enemies[], int size, Player *player, Explosion explosions[], int expSize);
void startExpolsion(Explosion explosions[], int x, int y, int size);

int main(int argc, char **argv)
{
    ALLEGRO_TRANSFORM t;
    ALLEGRO_DISPLAY *display         = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer             = NULL;
    ALLEGRO_FONT *font13             = NULL;
    ALLEGRO_BITMAP *bgImage          = NULL;
    ALLEGRO_BITMAP *playerImage      = NULL;
    ALLEGRO_BITMAP *enemyImage       = NULL;
    ALLEGRO_BITMAP *explosionImage   = NULL;


    Enemy enemies[ASTEROIDS_COUNT];
    Bullet bullets[BULLETS_COUNT];
    Player players[NUM_OF_PLAYERS];
    Explosion explosions[EXPLOSIONS_COUNT];
    Player *player = &players[0];
    Player playerLifes[2];//todo


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

    bgImage        = al_load_bitmap("11750.jpg");
    playerImage    = al_load_bitmap("ship.png");
    al_convert_mask_to_alpha(playerImage, al_map_rgb(255, 0, 255));
    explosionImage = al_load_bitmap("explosion.png");
    al_convert_mask_to_alpha(explosionImage, al_map_rgb(0, 0, 0));
    enemyImage     = al_load_bitmap("asteroid@50.png");
    event_queue    = al_create_event_queue();
    timer          = al_create_timer(1.0 / FPS);

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
            if (keys[UP]    && player->motion.y > HEIGHT / 3)   Player_move(player, NORTH);
            else if (keys[DOWN]  && player->motion.y < HEIGHT ) Player_move(player, SOUTH);
            else if (keys[RIGHT] && player->motion.x < WIDTH )  Player_move(player, EAST);
            else if (keys[LEFT]  && player->motion.x > 0)       Player_move(player, WEST);
            else Player_reset(player);

            controllEnemies(enemies, ASTEROIDS_COUNT);
            controllBullets(bullets, BULLETS_COUNT);
            collideBulletsAndEnemies(bullets, BULLETS_COUNT, enemies, ASTEROIDS_COUNT, player, explosions, EXPLOSIONS_COUNT);
            collideEnemiesAndPlayer(enemies, ASTEROIDS_COUNT, player, explosions, EXPLOSIONS_COUNT);
            //Explosion_start(explosion);

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
                drawEnemies(enemies, ASTEROIDS_COUNT);
                drawExplosions(explosions, EXPLOSIONS_COUNT);
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
    al_destroy_bitmap(explosionImage);
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

void collideBulletsAndEnemies(Bullet bullets[], int bSize, Enemy enemies[], int aSize, Player *player, Explosion explosions[], int expSize)
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



