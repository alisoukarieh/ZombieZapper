#ifndef _player_h
#define _player_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

typedef struct player {
    int x;
    int y;
    int health;
    SDL_Texture *texture;
} player;

player* create_player(int x, int y, int health, SDL_Texture *texture);
void move_player(player* p, int x, int y);
void input_player(player* p , SDL_Event event , int quit);


#endif