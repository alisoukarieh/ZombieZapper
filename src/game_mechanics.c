#include "./include/game_mechanics.h"

// Manage Collision between the player , zombies and bullets and add points when a zombie is hit by a bullet
void collision_manager(player* p , bullet_list** bl , zombie_list** zl , int* score ){
    bullet_list* current_bullet = *bl;
    zombie_list* current_zombie = *zl;
    int zombie_hit = 0;
    while (current_zombie != NULL){
        current_bullet = *bl;
        while (current_bullet != NULL){
            if ( SDL_HasIntersection( &(current_zombie->zombie->rect) , &(current_bullet->bullet->rect )) == SDL_TRUE ){
                    zombie_hit = 1; // skip collision check with player
                    *score += 1;
                    // skip current bullet and zombie
                    bullet_list* next_ptr_bullet = current_bullet->next ;
                    zombie_list* next_ptr_zombie = current_zombie->next ;
                    remove_zombie(zl,current_zombie->zombie);
                    remove_bullet(bl,current_bullet->bullet);
                    current_bullet = next_ptr_bullet ;
                    current_zombie = next_ptr_zombie ;
                    break;
            } else {
                current_bullet = current_bullet -> next;
            }
        }
        if ( zombie_hit == 0){
            if ( SDL_HasIntersection( &(current_zombie->zombie->rect) , &(p->rect )) == SDL_TRUE  && p->taking_damage == 0){
                p -> health -= 1;
                p -> taking_damage = 100; // invincibility and damage animation timer
            }
            current_zombie = current_zombie -> next;
        } else {
            zombie_hit = 0;

        }
    }
}

// Check if player is shooting
void shoot_checker( player* p , bullet_list** bl , SDL_Texture* bullet_texture) {
    if ( p -> shoot == 1){
        bullet* b = create_bullet( p , bullet_texture);
        add_bullet(bl , b);
        p -> shoot = 0;
    }
}

// Manage life count
SDL_Texture* health_manager(player* p  , int * scene_manager ,SDL_Texture* texture , SDL_Texture* texture2 , SDL_Texture* texture3) {
    if (p == NULL)
    {
        printf("Error: p is NULL in health_manager \n");
        exit(1);
    }
    // limit health to be between 0 and 3
    if (p->health  > 3){
        p->health = 3;
    } else if (p->health > 0){
        if (p->health > 2){
            return texture3;
        } else if (p->health > 1){
            return texture2;
        } else {
            return texture;
        }
    } else {
        p->health = 0;
        *scene_manager = 2;
    }
    return NULL;
}

// Manage buttons for all scenes
void buttons_manager ( Uint32 mouseState , SDL_Event event , int * quit  , int* scene_manager , int* reinitialize ,int* mouseX , int * mouseY){
    while (SDL_PollEvent(&event)) {

        switch (event.type) {
            case SDL_QUIT:
                *quit = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Get the current mouse state
                mouseState = SDL_GetMouseState(mouseX, mouseY);
                // Check if the left mouse button is pressed
                // main menu buttons
                if (mouseState && SDL_BUTTON(SDL_BUTTON_LEFT) && *mouseX >= play_button_x && *mouseX < play_button_x + play_button_w && *mouseY >= play_button_y && *mouseY < play_button_y + play_button_h && *scene_manager == 0) {
                    *scene_manager = 1 ;
                } else if (mouseState && SDL_BUTTON(SDL_BUTTON_LEFT) && *mouseX >= how_to_play_button_x && *mouseX < how_to_play_button_x + how_to_play_button_w && *mouseY >= how_to_play_button_y && *mouseY < how_to_play_button_y + how_to_play_button_h && *scene_manager == 0) {
                    *scene_manager = 3 ;
                } else if (mouseState && SDL_BUTTON(SDL_BUTTON_LEFT) && *mouseX >= quit_button_x && *mouseX < quit_button_x + quit_button_w && *mouseY >= quit_button_y && *mouseY < quit_button_y + quit_button_h && *scene_manager == 0) {
                    *quit = 1 ;
                }
                // game over buttons
                else if (mouseState && SDL_BUTTON(SDL_BUTTON_LEFT) && *mouseX >= play_again_button_x && *mouseX < play_again_button_x + play_again_button_w && *mouseY >= play_again_button_y && *mouseY < play_again_button_y + play_again_button_h && *scene_manager == 2) {
                    *reinitialize = 1 ;
                    *scene_manager = 1 ;
                } else if (mouseState && SDL_BUTTON(SDL_BUTTON_LEFT) && *mouseX >= quit_go_button_x && *mouseX < quit_go_button_x + quit_go_button_w && *mouseY >= quit_go_button_y && *mouseY < quit_go_button_y + quit_go_button_h && *scene_manager == 2) {
                    *quit = 1 ;
                }
                // how to play buttons
                else if (mouseState && SDL_BUTTON(SDL_BUTTON_LEFT) && *mouseX >= back_button_x && *mouseX < back_button_x + back_button_w && *mouseY >= back_button_y && *mouseY < back_button_y + back_button_h && *scene_manager == 3) {
                    *scene_manager = 0 ;
                }
                break;
        }
    }
}

// Free bullet list and zombie list
void free_all ( bullet_list** bl , zombie_list** zl ) {
    free_bullet_list(bl);
    free_zombie_list(zl);
}

// Load highscore from file
void loadHighScore(const char* filename , int* highscore) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        fscanf(file, "%d", highscore);
        fclose(file);
    } else {
        printf("Error loading high score.\n");
    }
}

// Save highscore in file
void saveHighScore(const char* filename , int highscore) {
    int lastScore;
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        fscanf(file, "%d", &lastScore);
        fclose(file);
    } else {
        lastScore = 0; // If highscore file doesn't exist, set the last score to 0
    }
    if (highscore > lastScore) {
        file = fopen(filename, "w");
        if (file != NULL) {
            fprintf(file, "%d", highscore);
            fclose(file);
            printf("New high score: %d\n", highscore);
        } else {
            printf("Error saving high score.\n");
        }
    }
}
