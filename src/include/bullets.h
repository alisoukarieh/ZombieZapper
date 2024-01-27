#ifndef _bullets_h
#define _bullets_h

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
// Create Bullet at the end of the gun's muzzle
bullet* create_bullet(player* p ,  SDL_Texture *texture);
// Add bullet to the bullet list
void add_bullet(bullet_list** bl, bullet* b);
// Remove bullet from the list
void remove_bullet(bullet_list** bl, bullet* b) ;
// Add bullet to the bullet list
void move_bullet(bullet* b);
// Move every bullet of a list using move_bullet function
void move_bullets(bullet_list** bl);
// Free Bullet List
void free_bullet_list(bullet_list** bl);


#endif
