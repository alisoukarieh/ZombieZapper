#include "./include/player.h"

// Create a player
player* create_player(int x, int y, int health, SDL_Texture *texture){
    player* p = malloc(sizeof(player));
    if (p == NULL){
        printf("Error: malloc failed in create_player \n");
        exit(1);
    }
    p->x = x;
    p->y = y;
    p->angle = 0;
    p->health = player_health;
    p->texture = texture;
    p->shoot = 0;
    p->taking_damage = 0;
    p->rect.x = x + player_collision_x_offset;
    p->rect.y = y + player_collision_y_offset;
    p->rect.w = player_collision_w;
    p->rect.h = player_collision_h;
    return p;
}

// Edit player coordinates 
void move_player(player* p, int x, int y){
    if (p == NULL){
        printf("Error: p is NULL in move_player \n");
        exit(1);
    }
    p->x += x;
    p->y += y;
    p->rect.x = p->x + player_collision_x_offset;
    p->rect.y = p->y + player_collision_y_offset;
}

// Manage input
void input_player( player* p , int *quit ){
    if (p == NULL){
        printf("Error: p is NULL in input_player \n");
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
                        if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W] ){
                            move_player(p, player_speed, -player_speed);
                        }
                        else if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S] ){
                            move_player(p, player_speed, player_speed);
                        } else {
                            move_player(p, player_speed, 0);
                        }
                    }
                    break;
                case SDLK_a:
                    if (p -> x > 0){
                        if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W] ){
                            move_player(p, -player_speed, -player_speed);
                        }
                        else if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S] ){
                            move_player(p, -player_speed, player_speed);
                        }
                        else{
                            move_player(p, -player_speed, 0);
                        }
                    }
                    break;  
                case SDLK_w:
                    if (p -> y > 0){
                        if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D] ){
                            move_player(p, player_speed, -player_speed);
                        }
                        else if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A] ){
                            move_player(p, -player_speed, -player_speed);
                        }
                        else{
                            move_player(p, 0, -player_speed);
                        }
                    }
                    break;
                case SDLK_s:
                    if (p -> y < SCREEN_HEIGHT - player_dim ){
                        if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D] ){
                            move_player(p, player_speed, player_speed);
                        }
                        else if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A] ){
                            move_player(p, -player_speed, player_speed);
                        }
                        else{
                            move_player(p, 0, player_speed);
                        }
                    }
                    break;
                }
  dw              break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    p->shoot = 1;
                }
                break;
        }
    }
}

// Make the player face the mouse
void rotate_player(player* p){
    if ( p == NULL)
    {
        printf("Error: p is NULL in rotate_player \n");
        exit(1);
    }
    
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    p->angle = atan2(mouseY - p->y, mouseX - p->x) ;
    p->angle = (p->angle) * (180.0 / M_PI);
}

