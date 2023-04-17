#include "./include/bullets.h"
#include "./include/player.h"
#include "./include/zombies.h"

bullet* create_bullet(player* p ,  SDL_Texture *texture){
    bullet* b = malloc(sizeof(bullet));
    if (b == NULL){
        printf("Error: malloc failed in create_bullet \n");
        exit(1);
    }
    // assign bullet position to player position with the offset and while taking into account the player angle
    b -> x = p->x + player_dim/2 + (player_gun_coord_x * cos(p->angle * M_PI / 180.0)) ;
    b -> y = p->y + player_dim/2 + (player_gun_coord_y * sin(p->angle * M_PI / 180.0)) ; 
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
        //exit(1);
    } else{
        b->x += bullet_speed * cos(b->angle * M_PI / 180.0);
        b->y += bullet_speed * sin(b->angle * M_PI / 180.0);
        b->rect.x = b->x;
        b->rect.y = b->y;
    }
}

void move_bullets(bullet_list** bl){
    if ( *bl == NULL)
    {
        printf("Error: bl is NULL in move_bullets \n");
        
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