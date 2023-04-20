#ifndef _player_h
#define _player_h

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

#define player_speed 10
#define player_dim 200
#define player_health 3
#define player_collision_x_offset 69
#define player_collision_y_offset 69
#define player_collision_w  61
#define player_collision_h  61
#define gun_r 83
#define gun_starting_angle 10

typedef struct player {
    int x;
    int y;
    double angle;
    int health;
    int shoot;
    int taking_damage;
    SDL_Texture *texture;
    SDL_Rect rect;
} player;

// Player Functions
player* create_player(int x, int y, int health, SDL_Texture *texture);
void move_player(player* p, int x, int y);
void input_player(player* p , int *quit);  
void rotate_player(player* p) ; 




#endif