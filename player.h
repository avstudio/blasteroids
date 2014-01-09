typedef struct
{
    int ID;
    int x;
    int y;
    float angle;
    int height;
    int width;
    int speed;
    ALLEGRO_COLOR color;
} Player;

void drawPlayer(Player *player);

void movePlayerRight(Player *player);
void movePlayerLeft(Player *player);
void movePlayerUp(Player *player);
void movePlayerDown(Player *player);