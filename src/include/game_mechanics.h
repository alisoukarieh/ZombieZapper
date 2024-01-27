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
#define difficulty_multiplier_speed 0.01
#define difficulty_multiplier_spawn 0.01

// Manage Collision between the player , zombies and bullets and add points when a zombie is hit by a bullet
void collision_manager(player* p , bullet_list** bl , zombie_list** zl  , int* score );
// Check if player is shooting
void shoot_checker( player* p , bullet_list** bl , SDL_Texture* bullet_texture) ;
// Manage buttons for all scenes
void buttons_manager ( Uint32 mouseState , SDL_Event event , int * quit  , int* scene_manager , int* reinitialize ,int* mouseX , int * mouseY) ;
// Free bullet list and zombie list
void free_all ( bullet_list** bl , zombie_list** zl ) ;
// Load highscore from file
void loadHighScore ( const char* filename , int* highScore ) ;
// Save highscore in file
void saveHighScore ( const char* filename , int highScore ) ;
// Manage life count
SDL_Texture* health_manager(player* p , int * scene_manager , SDL_Texture* texture , SDL_Texture* texture2 , SDL_Texture* texture3) ;
#endif
