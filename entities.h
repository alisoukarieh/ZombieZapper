#ifndef _entities_h
#define _entities_h


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "graphics.h"


#define player_speed 10
#define player_dim 200
#define player_dim_x 120 //170
#define player_dim_y 86 //100
#define player_gun_coord_x 29 // from the center of the player
#define player_gun_coord_y 0  // from the center of the player

#define bullet_speed 15
#define bullet_dim_x 30
#define bullet_dim_y 11

#define zombie_speed 1
#define zombie_dim 100



typedef struct player {
    int x;
    int y;
    double angle;
    int health;
    int shoot;
    SDL_Texture *texture;
    SDL_Rect rect;
} player;

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

// Player Functions
player* create_player(int x, int y, int health, SDL_Texture *texture);
void move_player(player* p, int x, int y);
void input_player(player* p , int *quit);  
void rotate_player(player* p) ; 

// Bullet Functions
bullet* create_bullet(player* p ,  SDL_Texture *texture);
void add_bullet(bullet_list** bl, bullet* b);
void remove_bullet(bullet_list** bl, bullet* b) ; 
void move_bullet(bullet* b);
void move_bullets(bullet_list** bl);
void free_bullet_list(bullet_list** bl);

// Zombie Functions
zombie* create_zombie( SDL_Texture *texture);
void move_zombie(zombie* z, player* p);
void add_zombie(zombie_list** zl, zombie* z);
void remove_zombie(zombie_list** zl, zombie* z) ;
void move_zombies(zombie_list** zl , player* p);
void free_zombie_list(zombie_list** zl);
void rotate_zombie(zombie* z , player* p) ;
void zombie_generator(zombie_list** zl , SDL_Texture *texture , int p) ;

// Game Mechanics
void collision_manager(player* p , bullet_list** bl , zombie_list** zl); 
void frame_drawer(SDL_Renderer* ecran , player* p , zombie_list* zl , bullet_list* bl);
void shoot_checker( player* p , bullet_list** bl , SDL_Texture* bullet_texture) ; 



#endif