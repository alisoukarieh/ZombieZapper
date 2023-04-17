#ifndef _bullets_h
#define _bullets_h


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

#define bullet_speed 15
#define bullet_dim_x 30
#define bullet_dim_y 11

typedef struct player player;
typedef struct zombie zombie;
typedef struct zombie_list zombie_list;

typedef struct bullet {
    float x;
    float y;
    double angle;
    SDL_Texture *texture;
    SDL_Rect rect;
} bullet;

typedef struct bullet_list {
    bullet *bullet;
    struct bullet_list *next;
} bullet_list;

// Bullet Functions
bullet* create_bullet(player* p ,  SDL_Texture *texture);
void add_bullet(bullet_list** bl, bullet* b);
void remove_bullet(bullet_list** bl, bullet* b) ; 
void move_bullet(bullet* b);
void move_bullets(bullet_list** bl);
void free_bullet_list(bullet_list** bl);


#endif