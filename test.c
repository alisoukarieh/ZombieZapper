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
    SDL_Window* fenetre=NULL;
    SDL_Renderer* ecran=NULL;
    init(&fenetre,&ecran,"ZombieZapper");
    player* p = create_player( 0 , 0 , 100 , NULL );
    p->texture = loadTexture(ecran,"./textures/player.bmp",&p->x,&p->y);
    drawTexture(ecran,p->texture,p->x,p->y, p->angle);

    int* quit = 0 ;   
    while ( quit == 0)
    {
        SDL_RenderClear(ecran);
        input_player(p ,quit);
        rotate_player(p);
        drawTexture(ecran,p->texture,p->x,p->y,p->angle);
        SDL_RenderPresent(ecran);

    }
    close(&fenetre,&ecran);
    
}


int main(int argc, char* argv[])
{
    player_movement_test();

    return 0;

}