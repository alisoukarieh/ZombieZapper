#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graphics.h"
#include "entities.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
    int  scene_manager = 0;


    // init window
    SDL_Window* fenetre=NULL;
    SDL_Renderer* ecran=NULL;
    init(&fenetre,&ecran,"ZombieZapper");

    // init player
    SDL_Texture* player_texture = loadTexture(ecran,"./textures/player3.bmp",0,0);
    SDL_Texture* damaged_player_texture = loadTexture(ecran,"./textures/damaged_player_2.bmp",0,0);
    player* p = create_player( 500 , 280 ,  player_health , player_texture );
    

    // init bullet
    SDL_Texture* bullet_texture = loadTexture(ecran,"./textures/bullet.bmp",0,0);
    bullet_list* bl = NULL; 

    // init zombie
    SDL_Texture* zombie_texture = loadTexture(ecran,"./textures/zombie.bmp",0,0);
    zombie_list* zl = NULL;

    // init background
    SDL_Texture* background_texture = loadTexture(ecran,"./textures/background2.bmp",0,0);

    // init health bar
    SDL_Texture* health_bar_texture = loadTexture(ecran,"./textures/1_heart.bmp",0,0);
    SDL_Texture* health_bar_texture2 = loadTexture(ecran,"./textures/2_hearts.bmp",0,0);
    SDL_Texture* health_bar_texture3 = loadTexture(ecran,"./textures/3_hearts.bmp",0,0);
    SDL_Texture* current_health_bar_texture = health_bar_texture;

    // init menu 
    SDL_Texture* main_menu_texture = loadTexture(ecran,"./textures/menu.bmp",0,0);

    // init gameover_screen 
    SDL_Texture* gameover_screen_texture = loadTexture(ecran,"./textures/GameOverScreen.bmp",0,0);

    // init how to play screen
    SDL_Texture* how_to_play_screen_texture = loadTexture(ecran,"./textures/how_to_play.bmp",0,0);

    // init mouse 
    int mouseX, mouseY;
    Uint32 mouseState;
    int quit = 0 ;   
    SDL_Event event;

    while ( quit == 0)
    {
        SDL_RenderClear(ecran);
        switch (scene_manager) {
            
            case 0 : 
                drawTexture(ecran,main_menu_texture,0,0,0);
                buttons_manager ( mouseState , event  , &quit , &scene_manager , &mouseX , &mouseY) ; 
                break;

            case 1 :
                current_health_bar_texture = health_manager(p, &scene_manager , health_bar_texture,health_bar_texture2,health_bar_texture3);
                input_player(p , &quit);
                rotate_player(p);
                zombie_generator(&zl , zombie_texture , 5) ;
                move_zombies(&zl , p);
                shoot_checker(p,&bl,bullet_texture);
                move_bullets(&bl);
                collision_manager(p,&bl,&zl);
                damage_animation(p, player_texture , damaged_player_texture);
                drawTexture(ecran,background_texture,0,0,0);
                frame_drawer(ecran,p,zl,bl,current_health_bar_texture);
                printf("player angle : %f \n" , p->angle);
                break;
            case 2 :
                // game over
                free_all(&bl , &zl) ; 
                drawTexture(ecran,gameover_screen_texture,0,0,0);
                buttons_manager ( mouseState , event  , &quit , &scene_manager , &mouseX , &mouseY) ;
                p -> health = player_health;
                p -> taking_damage = 0 ;
                p->x = 500;
                p->y = 280;
                p->rect.x = p->x;
                p->rect.y = p->y;
                break;
            case 3 :
                drawTexture(ecran,how_to_play_screen_texture,0,0,0);
                buttons_manager ( mouseState , event  , &quit , &scene_manager , &mouseX , &mouseY) ;
                break;
        }
        SDL_RenderPresent(ecran);
    }
    printf("1 \n") ; 
    if ( player_texture ) { SDL_DestroyTexture(player_texture); player_texture = NULL; }
    if ( damaged_player_texture ) { SDL_DestroyTexture(damaged_player_texture); damaged_player_texture = NULL; }
    if ( bullet_texture ) { SDL_DestroyTexture(bullet_texture); bullet_texture = NULL; }
    if ( zombie_texture ) { SDL_DestroyTexture(zombie_texture); zombie_texture = NULL; }
    if ( background_texture ) { SDL_DestroyTexture(background_texture); background_texture = NULL; }
    if ( health_bar_texture ) { SDL_DestroyTexture(health_bar_texture); health_bar_texture = NULL; }
    if ( health_bar_texture2 ) { SDL_DestroyTexture(health_bar_texture2); health_bar_texture2 = NULL; }
    if ( health_bar_texture3 ) { SDL_DestroyTexture(health_bar_texture3); health_bar_texture3 = NULL; }
    if ( main_menu_texture ) { SDL_DestroyTexture(main_menu_texture); main_menu_texture = NULL; }
    if ( gameover_screen_texture ) { SDL_DestroyTexture(gameover_screen_texture); gameover_screen_texture = NULL; }
    if ( how_to_play_screen_texture ) { SDL_DestroyTexture(how_to_play_screen_texture); how_to_play_screen_texture = NULL; }

    printf("2 \n") ; 

    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    free( p -> texture );
    free( p );
    free_all(&bl,&zl);
 
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
        printf("bullet pos : %f %f \n",tmp->bullet->x,tmp->bullet->y);
        tmp = tmp->next;
    }
    tmp = bl;
    remove_bullet(&bl,b2);
    while ( tmp != NULL)
    {
        printf("bullet pos : %f %f \n",tmp->bullet->x,tmp->bullet->y);
        tmp = tmp->next;
    }

    printf("end of list \n");

}


int main(int argc, char* argv[])
{
    player_movement_test();
    //list_testing();
    printf("end of program \n");
    return 0;

}
