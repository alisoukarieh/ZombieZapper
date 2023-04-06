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
    p->health = player_health;
    p->texture = texture;
    p->shoot = 0;
    p->taking_damage = 0;
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

    int z_x = rand() % ( SCREEN_WIDTH) - 100;
    int z_y = rand() % ( SCREEN_WIDTH) - 100;
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


void collision_manager(player* p , bullet_list** bl , zombie_list** zl  ){
    bullet_list* current_bullet = *bl;
    zombie_list* current_zombie = *zl;
    int zombie_hit = 0;
    while (current_zombie != NULL){
        current_bullet = *bl;
        while (current_bullet != NULL){
            if ( SDL_HasIntersection( &(current_zombie->zombie->rect) , &(current_bullet->bullet->rect )) == SDL_TRUE ){
                    zombie_hit = 1;
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
                p -> taking_damage = 100;
            }
            current_zombie = current_zombie -> next;
        } else {
            zombie_hit = 0;
            
        }
    }
}


void frame_drawer( SDL_Renderer* renderer , player* p , zombie_list* zl , bullet_list* bl , SDL_Texture* health_texture){
    
    
    drawTexture(renderer , p->texture , p->x , p->y , p->angle);
    drawTexture(renderer , health_texture , HEALTH_BAR_X , HEALTH_BAR_Y, 0);
    zombie_list* tmp = zl;
    while (tmp != NULL){
        drawTexture(renderer , tmp->zombie->texture , tmp->zombie->x , tmp->zombie->y , tmp->zombie->angle);
        tmp = tmp->next;
    }
    bullet_list* tmp2 = bl;
    while (tmp2 != NULL){
        drawTexture(renderer , tmp2->bullet->texture , tmp2->bullet->x , tmp2->bullet->y , tmp2->bullet->angle);
        tmp2 = tmp2->next;
    }
    SDL_RenderPresent(renderer);
    
}


void shoot_checker( player* p , bullet_list** bl , SDL_Texture* bullet_texture) {
    if ( p -> shoot == 1){
        bullet* b = create_bullet( p , bullet_texture);
        add_bullet(bl , b);
        p -> shoot = 0;
    } 
}

SDL_Texture* health_manager(player* p  , SDL_Texture* texture , SDL_Texture* texture2 , SDL_Texture* texture3) {
    if (p == NULL)
    {
        printf("Error: p is NULL in health_manager \n");
        exit(1);
    }
    // limit health to be between 0 and 30
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
    }
} 

void damage_animation( player* p , SDL_Texture* normal_player , SDL_Texture* damaged_player ){
    if ( p->taking_damage != 0 ){
        if (p->taking_damage % 5 == 0) {
            if (p->texture == normal_player){
                p->texture = damaged_player;
            } else {
                p->texture = normal_player;
            } 
            printf("taking damage %d") ; 
        }
        p->taking_damage -= 1;
    } else {
        p->texture = normal_player;
    }
}