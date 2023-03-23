#ifndef _entities_h
#define _entities_h


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "graphics.h"


#define player_speed 10
#define player_dim 250

#define bullet_speed 10

typedef stuct bullet {
    int x;
    int y;
    double angle;
    SDL_Texture *texture;
} bullet;

typedef struct player {
    int x;
    int y;
    double angle;
    int health;
    SDL_Texture *texture;
} player;




player* create_player(int x, int y, int health, SDL_Texture *texture);
void move_player(player* p, int x, int y);
void input_player(player* p , int *quit);  
void rotate_player(player* p) ; 




#endif