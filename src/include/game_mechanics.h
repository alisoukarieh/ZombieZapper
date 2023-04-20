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


// difficulty multiplier
#define spawn_probability 3
#define difficulty_multiplier_speed 0.05
#define difficulty_multiplier_spawn 0.01

void collision_manager(player* p , bullet_list** bl , zombie_list** zl  , int* score ); 
void shoot_checker( player* p , bullet_list** bl , SDL_Texture* bullet_texture) ; 
void buttons_manager ( Uint32 mouseState , SDL_Event event , int * quit  , int* scene_manager , int* reinitialize ,int* mouseX , int * mouseY) ; 
void free_all ( bullet_list** bl , zombie_list** zl ) ;
void loadHighScore ( const char* filename , int* highScore ) ;
void saveHighScore ( const char* filename , int highScore ) ;
SDL_Texture* health_manager(player* p , int * scene_manager , SDL_Texture* texture , SDL_Texture* texture2 , SDL_Texture* texture3) ; 
#endif