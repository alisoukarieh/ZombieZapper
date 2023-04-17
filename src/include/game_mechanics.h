#ifndef _game_mechanics_h
#define _game_mechanics_h


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "bullets.h"
#include "zombies.h"
#include <math.h>
#include "graphics.h"

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

void collision_manager(player* p , bullet_list** bl , zombie_list** zl ); 
void frame_drawer(SDL_Renderer* ecran , player* p , zombie_list* zl , bullet_list* bl, SDL_Texture* health_texture);
void shoot_checker( player* p , bullet_list** bl , SDL_Texture* bullet_texture) ; 
void damage_animation(  player* p , SDL_Texture* normal_player , SDL_Texture* damaged_player );
void buttons_manager ( Uint32 mouseState , SDL_Event event , int * quit  , int* scene_manager ,int* mouseX , int * mouseY) ; 
void free_all ( bullet_list** bl , zombie_list** zl ) ;

#endif