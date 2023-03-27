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
    p->rect.x = x;
    p->rect.y = y;
    p->rect.w = player_dim;
    p->rect.h = player_dim;
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
    p->rect.x = p->x;
    p->rect.y = p->y;
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
    // assign bullet position to player position with the offset and while taking into account the player angle
    b -> x = p->x + player_dim/2 + player_gun_coord_x * cos(p->angle * M_PI / 180.0) ;
    b -> y = p->y + player_dim/2 + player_gun_coord_y * sin(p->angle * M_PI / 180.0) ; 
    b->angle = p->angle;
    b->texture = texture;
    b->rect.x = b->x;
    b->rect.y = b->y;
    b->rect.w = bullet_dim_x;
    b->rect.h = bullet_dim_y;

    
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



void move_bullet(bullet* b) {
    if ( b == NULL)
    {
        printf("Error: b is NULL in move_bullet \n");
        exit(1);
    }
    b->x += bullet_speed * cos(b->angle * M_PI / 180.0);
    b->y += bullet_speed * sin(b->angle * M_PI / 180.0);
    b->rect.x = b->x;
    b->rect.y = b->y;


}

void move_bullets(bullet_list** bl){
    if ( *bl == NULL)
    {
        //printf("Error: bl is NULL in move_bullets \n");
        
    } else {
        bullet_list* tmp = *bl;
        while (tmp != NULL){
            // stop moving the bullet if it is out of the screen
            if ( ! ( tmp->bullet->x < 0 || tmp->bullet->x > SCREEN_WIDTH || tmp->bullet->y < 0 || tmp->bullet->y > SCREEN_HEIGHT ) ){
                move_bullet(tmp->bullet);
            } else {
                remove_bullet(bl, tmp->bullet); 
            }
            tmp = tmp->next;
        }
    }
}


// remove bullet from the list
void remove_bullet(bullet_list** bl, bullet* b){
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
    bullet_list* prev = NULL;
    while (tmp != NULL){
        if (tmp->bullet == b){
            if (prev == NULL){
                (*bl) = tmp->next;
            } else {
                prev->next = tmp->next;
            }
            free(tmp -> bullet -> texture);
            free(tmp -> bullet);
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}


zombie* create_zombie(SDL_Texture *texture){
    zombie* z = malloc(sizeof(zombie));
    if (z == NULL){
        printf("Error: malloc failed in create_zombie \n");
        exit(1);
    }

    z->texture = texture;
    z->rect.x = z->x;
    z->rect.y = z->y;
    z->rect.w = zombie_dim;
    z->rect.h = zombie_dim;
    z -> angle = 0;

    int z_x = rand() % (2 * SCREEN_WIDTH) - SCREEN_WIDTH;
    int z_y = rand() % (2 * SCREEN_WIDTH) - SCREEN_HEIGHT;
    if (z_x > 0) {
        z_x += SCREEN_WIDTH;
    } else {
        z_x -= SCREEN_WIDTH;
    }
    
    if (z_y > 0) {
        z_y += SCREEN_HEIGHT;
    } else {
        z_y -= SCREEN_HEIGHT;
    }

    z->x = z_x;
    z->y = z_y;


    return z;
}

void add_zombie(zombie_list** zl, zombie* z){
    if ( z == NULL)
    {
        printf("Error: z is NULL in add_zombie \n");
        exit(1);
    }
    if ( (*zl) == NULL)
    {
        (*zl)= malloc(sizeof(zombie_list));
        (*zl) -> zombie = z;
        (*zl) -> next = NULL;
    } else {
        zombie_list* tmp = (*zl);
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp -> next = malloc(sizeof(zombie_list));
        if (tmp -> next == NULL){
            printf("Error: malloc failed in add_zombie \n");
            exit(1);
        }
        tmp = tmp -> next;
        tmp -> zombie = z;
        tmp -> next = NULL;
    }

}

void remove_zombie(zombie_list** zl, zombie* z){
    if ( z == NULL)
    {
        printf("Error: z is NULL in remove_zombie \n");
        exit(1);
    }
    if ( (*zl) == NULL)
    {
        printf("Error: zl is NULL in remove_zombie \n");
        exit(1);
    }
    zombie_list* tmp = (*zl);
    zombie_list* prev = NULL;
    while (tmp != NULL){
        if (tmp->zombie == z){
            if (prev == NULL){
                (*zl) = tmp->next;
            } else {
                prev->next = tmp->next;
            }
            free(tmp -> zombie -> texture);
            free(tmp -> zombie);
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void move_zombie(zombie* z , player* p ){
    if ( z == NULL)
    {
        printf("Error: z is NULL in move_zombie \n");
        exit(1);
    }
    // move the zombie towards the player
    if (z->x < p->x){
        z->x += zombie_speed;
    } else if (z->x > p->x){
        z->x -= zombie_speed;
    }
    if (z->y < p->y){
        z->y += zombie_speed;
    } else if (z->y > p->y){
        z->y -= zombie_speed;
    }
    z->rect.x = z->x;
    z->rect.y = z->y;
    // rotate the zombie towards the player
    rotate_zombie(z ,p);
}

void move_zombies(zombie_list** zl , player* p){
    if ( *zl == NULL)
    {
        //printf("Error: zl is NULL in move_zombies \n");
        return;
        
    } else {
        zombie_list* tmp = *zl;
        while (tmp != NULL){
            move_zombie(tmp->zombie , p);
            tmp = tmp->next;
        }
    }
}

void free_bullet_list(bullet_list** bl){
    if ( *bl == NULL)
    {
        printf("Error: bl is NULL in free_bullet_list \n");
        
    } else {
        bullet_list* tmp = *bl;
        while (tmp != NULL){
            bullet_list* next = tmp->next;
            free(tmp);
            tmp = next;
        }
        *bl = NULL;
    }
}

void free_zombie_list(zombie_list** zl){
    if ( *zl == NULL)
    {
        printf("Error: zl is NULL in free_zombie_list \n");
        
    } else {
        zombie_list* tmp = *zl;
        while (tmp != NULL){
            zombie_list* next = tmp->next;
            free(tmp);
            tmp = next;
        }
        *zl = NULL;
    }
}

void rotate_zombie ( zombie* z , player* p ){
    if ( z == NULL)
    {
        printf("Error: z is NULL in rotate_zombie \n");
        exit(1);
    }
    if ( p == NULL)
    {
        printf("Error: p is NULL in rotate_zombie \n");
        exit(1);
    }
    // rotate the zombie towards the player
    z->angle = atan2( (p->y - z->y) , (p->x - z->x) ) * 180 / M_PI;
    // double cos_angle = (p->x - z->x) / sqrt( (p->x - z->x)*(p->x - z->x) + (p->y - z->y)*(p->y - z->y) );
    // z->angle = acos(cos_angle) * 180 / M_PI;

}

void zombie_generator(zombie_list** zl , SDL_Texture* texture , int p) {
    int x = rand() % 100;
    if (x < p){
        add_zombie(zl , create_zombie(texture));
    }
} 