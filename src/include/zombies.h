#ifndef _zombies_h
#define _zombies_h


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

#define zombie_speed 2
#define zombie_dim 100
#define zombie_collision_x_offset 15
#define zombie_collision_y_offset 15
#define zombie_collision_w  70
#define zombie_collision_h  70

typedef struct player player;

typedef struct zombie_list {
    struct zombie *zombie;
    struct zombie_list *next;
} zombie_list;

typedef struct zombie {
    float x;
    float y;
    int health;
    SDL_Texture *texture;
    SDL_Rect rect;
    double angle;
} zombie;

// Zombie Functions
// Create Zombie
zombie* create_zombie( SDL_Texture *texture);
// Move zombie towards the player
void move_zombie(zombie* z, player* p , int score , float difficulty);
// Add zombie to zombie list
void add_zombie(zombie_list** zl, zombie* z);
// Remove zombie from zombie list
void remove_zombie(zombie_list** zl, zombie* z) ;
// Move all zombies towards the player using move_zombie function
void move_zombies(zombie_list** zl , player* p ,int score , float difficulty);
// Free zombie list
void free_zombie_list(zombie_list** zl);
// Make zombie face the player
void rotate_zombie(zombie* z , player* p) ;
// Generate zombies based on a spawn rate as well as score
void zombie_generator(zombie_list** zl , SDL_Texture *texture , int p , int score , float difficulty) ;

#endif
