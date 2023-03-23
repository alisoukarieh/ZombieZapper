#include "entities.h"

// Create a player
player* create_player(int x, int y, int health, SDL_Texture *texture){
    player* p = malloc(sizeof(player));
    if (p == NULL){
        printf("Error: malloc failed in create_player");
        exit(1);
    }
    p->x = x;
    p->y = y;
    p->angle = 0;
    p->health = health;
    p->texture = texture;
    return p;
}

// Edit player coordinates 
void move_player(player* p, int x, int y){
    if (p == NULL){
        printf("Error: p is NULL in move_player");
        exit(1);
    }
    p->x += x;
    p->y += y;
}

// Manage input
void input_player( player* p , int *quit ){
    if (p == NULL){
        printf("Error: p is NULL in input_player");
        exit(1);
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *quit = 1;
                break;
            case SDL_KEYDOWN:
                switch ( event.key.keysym.sym)
                {
                case SDLK_d:
                    if ( p -> x < SCREEN_WIDTH - player_dim )
                    {
                        move_player(p, player_speed, 0);
                    }
                    break;
                case SDLK_a:
                    if (p -> x > 0){
                        move_player(p, -player_speed, 0);
                    }
                    break;  
                case SDLK_w:
                    if (p -> y > 0){
                        move_player(p, 0, -player_speed);
                    }
                    break;
                case SDLK_s:
                    if (p -> y < SCREEN_HEIGHT - player_dim ){
                        move_player(p, 0, player_speed);
                    }
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    printf("left click");
                    // shooting bullet function
                }
                break;
        }
    }
}

// Make the player face the mouse
void rotate_player(player* p){
    if ( p == NULL)
    {
        printf("Error: p is NULL in rotate_player");
        exit(1);
    }
    
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    p->angle = atan2(mouseY - p->y, mouseX - p->x) ;
    p->angle = (p->angle) * (180.0 / M_PI);
}


