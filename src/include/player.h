#ifndef _player_h
#define _player_h

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

#define player_speed 10
#define player_dim 200
#define player_dim_x 120 //170
#define player_dim_y 86 //100
#define player_gun_coord_x 75 //73 // from the center of the player
#define player_gun_coord_y 14  // from the center of the player
#define player_health 3
#define player_collision_x_offset 82
#define player_collision_y_offset 72
#define player_collision_w  60
#define player_collision_h  80

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
SDL_Texture* health_manager(player* p , int * scene_manager , SDL_Texture* texture , SDL_Texture* texture2 , SDL_Texture* texture3) ; 



#endif