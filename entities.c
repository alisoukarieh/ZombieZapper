#include "entities.h"

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
    p->health = health;
    p->texture = texture;
    p->shoot = 0;
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
                    p->shoot = 1;
                    printf("player position : %d , %d \n" , p->x , p->y);
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

bullet* create_bullet(player* p ,  SDL_Texture *texture){
    bullet* b = malloc(sizeof(bullet));
    if (b == NULL){
        printf("Error: malloc failed in create_bullet \n");
        exit(1);
    }
    b->x = ((p->x + player_gun_coord_x) * cos(p->angle * M_PI / 180.0 ) );
    b->y = ((p->y + player_gun_coord_y) * sin(p->angle * M_PI / 180.0 ));
    b->angle = p->angle;
    b->texture = texture;
    return b;
}


void add_bullet(bullet_list** bl, bullet* b){
    if ( b == NULL)
    {
        printf("Error: b is NULL in add_bullet \n");
        exit(1);
    }
    if ( (*bl) == NULL)
    {
        (*bl)= malloc(sizeof(bullet_list));
        (*bl) -> bullet = b;
        (*bl) -> next = NULL;
        printf("bl is null \n");
    } else {
        //printf("bl is not null");
        bullet_list* tmp = (*bl);
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp -> next = malloc(sizeof(bullet_list));
        if (tmp -> next == NULL){
            printf("Error: malloc failed in add_bullet \n");
            exit(1);
        }
        tmp = tmp -> next;
        tmp -> bullet = b;
        tmp -> next = NULL;
    }

}

void remove_bullet ( bullet_list **bl , bullet *b){
    if ( b == NULL)
    {
        printf("Error: b is NULL in remove_bullet \n");
        exit(1);
    }
    if ( (*bl) == NULL)
    {
        printf("Error: bl is NULL in remove_bullet \n");
        exit(1);
    }
    bullet_list* tmp = (*bl);
    if (tmp->bullet == b){
        (*bl) = tmp->next;
        free(tmp->bullet);
    } else {
        while (tmp->next != NULL){
            if (tmp->next->bullet == b){
                bullet_list* tmp2 = tmp->next;
                tmp->next = tmp->next->next;
                free(tmp2->bullet);
                free(tmp2);
                break;
            }
            tmp = tmp->next;
        }
    }
    free(tmp);
}

void move_bullet(bullet* b) {
    if ( b == NULL)
    {
        printf("Error: b is NULL in move_bullet \n");
        exit(1);
    }
    b->x += bullet_speed * cos(b->angle  * M_PI / 180.0);
    b->y += bullet_speed * sin(b->angle * M_PI / 180.0);

}

void move_bullets(bullet_list** bl){
    if ( *bl == NULL)
    {
        printf("Error: bl is NULL in move_bullets \n");
        
    } else {
        bullet_list* tmp = *bl;
        
        while (tmp != NULL){
            if (tmp->bullet->x < 0 || tmp->bullet->x > SCREEN_WIDTH || tmp->bullet->y < 0 || tmp->bullet->y > SCREEN_HEIGHT){
                printf("remove bullet \n");
                remove_bullet(bl, tmp->bullet);

            } else {
                move_bullet(tmp->bullet);
            }
            tmp = tmp->next;
        }
    }
}
    
