#ifndef _window_h
#define _window_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

// taille fenetre
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// bool 
#define FALSE 0
#define TRUE 1

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

#endif 