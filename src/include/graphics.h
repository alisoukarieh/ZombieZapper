#ifndef _window_h
#define _window_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "player.h"
#include "bullets.h"
#include "zombies.h"


// taille fenetre
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// bool
#define FALSE 0
#define TRUE 1

// Health bar position
#define HEALTH_BAR_X 640 - 95
#define HEALTH_BAR_Y 650

#define score_x 31
#define score_y 26

// Menu
#define highscore_menu_x 651
#define highscore_menu_y 181
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

// GameOver Screen
#define highscore_gameover_x 657
#define highscore_gameover_y 233
#define score_gameover_x 657
#define score_gameover_y 288
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


#define score_value_x 200
#define score_value_y 30


// Init SDL
int init(SDL_Window** gWindow,SDL_Renderer** gRenderer, char* nameWindow) ;

// Return a SDL_Texture from a file
void close(SDL_Window** gWindow,SDL_Renderer** gRenderer) ;

// Return a SDL_Texture from a file
SDL_Texture* loadTexture(SDL_Renderer *gRenderer,char *file_name_bmp,int *size_w, int *size_h) ;

// Draw a SDL_Texture at position x, y
void drawTexture (SDL_Renderer *gRenderer,SDL_Texture *texture,int x, int y, double angle) ;

// Initialize digits textures
void score_init(SDL_Renderer* renderer , SDL_Texture** digits) ;

//Draw digit textures corresponding to the score
void score_update(int score, SDL_Renderer* renderer, SDL_Texture** digits , int x , int y) ;

// Draw all textures that make a frame
void frame_drawer(SDL_Renderer* ecran , player* p , zombie_list* zl , bullet_list* bl, SDL_Texture* health_texture , SDL_Texture* score_texture);

// Change player textures to make damage animation
void damage_animation(  player* p , SDL_Texture* normal_player , SDL_Texture* damaged_player );

#endif
