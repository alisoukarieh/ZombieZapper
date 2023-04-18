#ifndef _window_h
#define _window_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <string.h>

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

// Init SDL
int init(SDL_Window** gWindow,SDL_Renderer** gRenderer, char* nameWindow) ; 

// Return a SDL_Texture from a file
void close(SDL_Window** gWindow,SDL_Renderer** gRenderer) ; 

// Return a SDL_Texture from a file
SDL_Texture* loadTexture(SDL_Renderer *gRenderer,char *file_name_bmp,int *size_w, int *size_h) ; 

// Draw a SDL_Texture at position x, y
void drawTexture (SDL_Renderer *gRenderer,SDL_Texture *texture,int x, int y, double angle) ;

SDL_Texture* creerTextureSorbonne(SDL_Renderer *ecran,char *nom_file_bmp,int *size_w, int *size_h) ;

void dessine_sorbonne(SDL_Renderer *ecran,SDL_Texture *sorbonneTexture,int x, int y) ;

void score_init(SDL_Renderer* renderer , SDL_Texture** digits) ;
void score_update(int score, SDL_Renderer* renderer, SDL_Texture** digits) ;

#endif 