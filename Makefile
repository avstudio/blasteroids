CFLAGS= -Wall

LDFLAGS=-L~/allegro/build/lib  -lallegro
CC=gcc
# INCLUDE BASE DIRECTORY AND BOOST DIRECTORY FOR HEADERS
LDFLAGS = -I/opt/local/include -I./includes

# INCLUDE BASE DIRECTORY AND BOOST DIRECTORY FOR LIB FILES
LLIBFLAGS =  -L/usr/local/lib

# SPECIFIY LINK OPTIONS
LINKFLAGS =  -lallegro.5.0.10 -lallegro_main.5.0.10 -lallegro_font.5.0.10 -lallegro_ttf.5.0.10 -lallegro_primitives.5.0.10 -lallegro_dialog.5.0.10

# FINAL FLAGS -- TO BE USED THROUGHOUT
FLAGS = $(LDFLAGS) $(LLIBFLAGS) $(LINKFLAGS)

all: clean  blasteroids

asteroid.c:
	$(CC) $(FLAGS) -c asteroid.c -o asteroid.o $(FLAGS)

collision.c:
	$(CC) $(FLAGS) -c collision.c -o collision.o $(FLAGS)

bullet.c:
	$(CC) $(FLAGS) -c bullet.c -o bullet.o $(FLAGS)

player.c:
	$(CC) $(FLAGS) -c player.c -o player.o $(FLAGS)

blasteroids.o: player.c asteroid.c bullet.c collision.c
	$(CC) $(FLAGS) -c blasteroids.c -o blasteroids.o $(FLAGS)

blasteroids: blasteroids.o player.o asteroid.o bullet.o collision.o
	$(CC) blasteroids.o player.o asteroid.o bullet.o collision.o  -o blasteroids $(FLAGS)

clean:
	rm -rf *o ./blasteroids