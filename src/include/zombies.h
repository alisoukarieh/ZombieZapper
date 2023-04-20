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
    int x;
    int y;
    int health;
    SDL_Texture *texture;
    SDL_Rect rect;
    double angle;
} zombie;

// Zombie Functions
zombie* create_zombie( SDL_Texture *texture);
void move_zombie(zombie* z, player* p , int score , float difficulty);
void add_zombie(zombie_list** zl, zombie* z);
void remove_zombie(zombie_list** zl, zombie* z) ;
void move_zombies(zombie_list** zl , player* p ,int score , float difficulty);
void free_zombie_list(zombie_list** zl);
void rotate_zombie(zombie* z , player* p) ;
void zombie_generator(zombie_list** zl , SDL_Texture *texture , int p , int score , float difficulty) ;

#endif