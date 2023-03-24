#ifndef _entities_h
#define _entities_h


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "graphics.h"


#define player_speed 10
#define player_dim 200
#define player_dim_x 170
#define player_dim_y 100
#define player_gun_coord_x 85 // from the center of the player
#define player_gun_coord_y 50 //30 // from the center of the player

#define bullet_speed 10
#define bullet_dim_x 30
#define bullet_dim_y 11



typedef struct player {
    int x;
    int y;
    double angle;
    int health;
    int shoot;
    SDL_Texture *texture;
} player;

typedef struct bullet {
    float x;
    float y;
    double angle;
    SDL_Texture *texture;
} bullet;

typedef struct bullet_list {
    bullet *bullet;
    struct bullet_list *next;
} bullet_list;



player* create_player(int x, int y, int health, SDL_Texture *texture);
void move_player(player* p, int x, int y);
void input_player(player* p , int *quit);  
void rotate_player(player* p) ; 

bullet* create_bullet(player* p ,  SDL_Texture *texture);
void add_bullet(bullet_list** bl, bullet* b);
void remove_bullet(bullet_list** bl, bullet* b) ; 
void move_bullet(bullet* b);
void move_bullets(bullet_list** bl);




#endif