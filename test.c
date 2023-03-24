#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graphics.h"
#include "entities.h"
#include <SDL2/SDL.h>


// int opening_window_test()
// {
//     SDL_Window* fenetre=NULL;
//     SDL_Renderer* ecran=NULL;

//     init(&fenetre,&ecran,"ZombieZapper");
//     SDL_Delay(5000);
//     close(&fenetre,&ecran);

//     return 0;
// }

// void loading_player_texture_test(){
//     SDL_Window* fenetre=NULL;
//     SDL_Renderer* ecran=NULL;
//     init(&fenetre,&ecran,"ZombieZapper");
//     player* p = create_player( 0 , 0 , 100 , NULL );
//     p->texture = loadTexture(ecran,"./textures/player.bmp",&p->x,&p->y);
//     drawTexture(ecran,p->texture,p->x,p->y,p->angle);
     

//     SDL_RenderPresent(ecran);
//     SDL_Delay(5000);
//     close(&fenetre,&ecran);

// }

void player_movement_test(){
    // init window
    SDL_Window* fenetre=NULL;
    SDL_Renderer* ecran=NULL;
    init(&fenetre,&ecran,"ZombieZapper");

    // init player
    SDL_Texture* player_texture = loadTexture(ecran,"./textures/player.bmp",0,0);
    player* p = create_player( 0 , 0 , 100 , player_texture );
    // drawTexture(ecran,p->texture,p->x,p->y, p->angle);

    // init bullet
    SDL_Texture* bullet_texture = loadTexture(ecran,"./textures/bullet.bmp",0,0);
    // drawTexture(ecran,bullet_texture,100,100,0);
    bullet_list* bl = NULL; 

    

    int* quit = 0 ;   
    while ( quit == 0)
    {
        SDL_RenderClear(ecran);
        input_player(p ,quit);
        rotate_player(p);
        drawTexture(ecran,p->texture,p->x,p->y,p->angle);
        if ( p -> shoot == 1)
        {
            printf(" player position : %d , %d \n" , p -> x , p -> y) ; 
            bullet* b = create_bullet(p ,bullet_texture);
            // drawTexture(ecran,b->texture,b->x,b->y,b->angle);
            add_bullet(&bl,b);

            p -> shoot = 0;
            
        }

        move_bullets(&bl);
        bullet_list* tmp = bl;
        while ( tmp != NULL)
        {
            printf(" bullet position : %d , %d \n" , tmp -> bullet -> x , tmp -> bullet -> y ) ;
            drawTexture(ecran,tmp->bullet->texture,tmp->bullet->x,tmp->bullet->y,tmp->bullet->angle);
            
            tmp = tmp->next;
        }

        // Handle shooting
        // if (p->shoot == 1){
        //     bullet* b = create_bullet(p,bullet_texture);
        //     printf(" bullet created \n") ;
        //     add_bullet(&bl,b);  
        //     //printf(" bullet pos : %d\n" , bl->bullet->x) ;
        //     bullet_list* tmp = bl;
        //     while ( tmp != NULL)
        //     {
        //         move_bullet(tmp->bullet);
        //         drawTexture(ecran,tmp->bullet->texture,tmp->bullet->x,tmp->bullet->y,tmp->bullet->angle);
        //         tmp = tmp->next;
        //     }
        //     p->shoot = 0;
        // }
        SDL_RenderPresent(ecran);
    }

    close(&fenetre,&ecran);
    
}

void list_testing(){    
    SDL_Window* fenetre=NULL;
    SDL_Renderer* ecran=NULL;
    init(&fenetre,&ecran,"ZombieZapper");

    SDL_Texture* player_texture = loadTexture(ecran,"./textures/player.bmp",0,0) ; 
    player* p = create_player( 10 , 10 , 100 , player_texture );


    SDL_Texture* bullet_texture = loadTexture(ecran,"./textures/bullet.bmp",0,0);

    bullet_list* bl = NULL;

    bullet* b1 = create_bullet(p,bullet_texture);
    move_player(p,10,10);
    bullet* b2 = create_bullet(p,bullet_texture);
    move_player(p,10,10);
    bullet* b3 = create_bullet(p,bullet_texture);

    add_bullet(&bl,b1);
    add_bullet(&bl,b2);
    add_bullet(&bl,b3);

    bullet_list* tmp = bl;
    while ( tmp != NULL)
    {
        printf("bullet pos : %d %d \n",tmp->bullet->x,tmp->bullet->y);
        tmp = tmp->next;
    }
    tmp = bl;
    remove_bullet(&bl,b2);
    while ( tmp != NULL)
    {
        printf("bullet pos : %d %d \n",tmp->bullet->x,tmp->bullet->y);
        tmp = tmp->next;
    }

    printf("end of list \n");

    


}


int main(int argc, char* argv[])
{
    player_movement_test();
    //list_testing();

    return 0;

}