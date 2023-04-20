#include "./include/zombies.h"
#include "./include/player.h"
#include "./include/bullets.h"

zombie* create_zombie(SDL_Texture *texture){
    zombie* z = malloc(sizeof(zombie));
    if (z == NULL){
        printf("Error: malloc failed in create_zombie \n");
        exit(1);
    }

    z->texture = texture;
    z->rect.x = z->x + zombie_collision_x_offset;
    z->rect.y = z->y + zombie_collision_y_offset;
    z->rect.w = zombie_collision_w;
    z->rect.h = zombie_collision_h;
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

void move_zombie(zombie* z , player* p , int score , float difficulty){
    int multiplier = 1;
    if ( z == NULL)
    {
        printf("Error: z is NULL in move_zombie \n");
        exit(1);
    }
    // if out of bounds , move faster
    if (z->x < -100 || z->x > SCREEN_WIDTH+100 || z->y < -100 || z->y > SCREEN_HEIGHT + 100){
        multiplier = 10;
    } else {
        multiplier = 1 + score*difficulty;
    }
    int delta_x = p->x + player_dim/2 - z->x - zombie_dim/2;
    int delta_y = p->y + player_dim/2 - z->y - zombie_dim/2;

    double distance = sqrt( delta_x * delta_x + delta_y * delta_y );

    if (distance!=0){
        z->x += (delta_x / distance) * zombie_speed * multiplier;
        z->y += (delta_y / distance) * zombie_speed * multiplier;

        z->rect.x = z->x + zombie_collision_x_offset;
        z->rect.y = z->y + zombie_collision_y_offset;
        rotate_zombie(z ,p);
    }
    
}

void move_zombies(zombie_list** zl , player* p , int score , float difficulty){
    if ( *zl == NULL)
    {
        return;
    } else {
        zombie_list* tmp = *zl;
        while (tmp != NULL){
            move_zombie(tmp->zombie , p , score , difficulty);
            tmp = tmp->next;
        }
    }
}

void free_zombie_list(zombie_list** zl){
    if ( *zl == NULL)
    {
        return ;
        
    } else {
        zombie_list* tmp = *zl;
        while (tmp -> next != NULL){
            zombie_list* next = tmp->next;
            free(tmp -> zombie -> texture);
            free(tmp -> zombie);
            tmp = next;
        }
        free(tmp);
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

void zombie_generator(zombie_list** zl , SDL_Texture* texture , int p , int score , float difficulty_multiplier) {
    float x = rand() % 100;
    if (x  < p + score*difficulty_multiplier){
        add_zombie(zl , create_zombie(texture));
    }
} 