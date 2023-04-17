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
#define player_gun_coord_x 75 //73 // from the center of the player
#define player_gun_coord_y 14  // from the center of the player
#define player_health 3
#define player_collision_x_offset 82
#define player_collision_y_offset 72
#define player_collision_w  60
#define player_collision_h  80

#define bullet_speed 15
#define bullet_dim_x 30
#define bullet_dim_y 11

#define zombie_speed 2
#define zombie_dim 100

// Menu buttons
// play button  
#define play_button_x 560
#define play_button_y 310
#define play_button_w 160
#define play_button_h 50 

// how to play button
#define how_to_play_button_x 426
#define how_to_play_button_y 409
#define how_to_play_button_w 438
#define how_to_play_button_h 52

// quit button
#define quit_button_x 562
#define quit_button_y 520
#define quit_button_w 155
#define quit_button_h 50

// How to play screen buttons
// back button
#define back_button_x 67
#define back_button_y 629
#define back_button_w 177
#define back_button_h 54

// GameOver Screen Buttons
// Play Again Button
#define play_again_button_x 450
#define play_again_button_y 360
#define play_again_button_w 383
#define play_again_button_h 52

// Quit Button
#define quit_go_button_x 569
#define quit_go_button_y 455
#define quit_go_button_w 142
#define quit_go_button_h 51





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
SDL_Texture* health_manager(player* p , int * scene_manager , SDL_Texture* texture , SDL_Texture* texture2 , SDL_Texture* texture3) ; 

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
void collision_manager(player* p , bullet_list** bl , zombie_list** zl ); 
void frame_drawer(SDL_Renderer* ecran , player* p , zombie_list* zl , bullet_list* bl, SDL_Texture* health_texture);
void shoot_checker( player* p , bullet_list** bl , SDL_Texture* bullet_texture) ; 
void damage_animation(  player* p , SDL_Texture* normal_player , SDL_Texture* damaged_player );
void buttons_manager ( Uint32 mouseState , SDL_Event event , int * quit  , int* scene_manager ,int* mouseX , int * mouseY) ; 
void free_all ( bullet_list** bl , zombie_list** zl ) ;
#endif