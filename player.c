#include "player.h"

player* create_player(int x, int y, int health, SDL_Texture *texture){
    player* p = malloc(sizeof(player));
    p->x = x;
    p->y = y;
    p->health = health;
    p->texture = texture;
    return p;
}

// Player Movement 
void move_player(player* p, int x, int y){
    p->x += x;
    p->y += y;
}

void input_player(player* p , SDL_Event e , int quit){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                // The user closed the window
                quit = 1;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_d) {
                    // 'd' key was pressed
                    move_player(p, 10, 0);
                    printf("d");
                }
                if (event.key.keysym.sym == SDLK_a) {
                    // 'q' key was pressed
                    move_player(p, -10, 0);
                    printf("q");
                }
                if (event.key.keysym.sym == SDLK_w) {
                    // 'z' key was pressed
                    move_player(p, 0, -10);
                    printf("z");
                }
                if (event.key.keysym.sym == SDLK_s) {
                    // 's' key was pressed
                    move_player(p, 0, 10);
                    printf("s");
                }
                if ( event.key.keysym.sym == SDLK_d && event.key.keysym.sym == SDLK_w){
                    move_player(p, 10, 10);
                }
                if ( event.key.keysym.sym == SDLK_d && event.key.keysym.sym == SDLK_s){
                    move_player(p, 10, -10);
                }
                if ( event.key.keysym.sym == SDLK_a && event.key.keysym.sym == SDLK_w){
                    move_player(p, -10, 10);
                }
                if ( event.key.keysym.sym == SDLK_a && event.key.keysym.sym == SDLK_s){
                    move_player(p, -10, -10);
                }
                
                
                break;
            case SDL_MOUSEBUTTONDOWN:
                // A mouse button was pressed
                break;
            // Add more cases for other events as needed
        }
    }
}

// void input_player(player* p , SDL_Event e , int quit){
//     SDL_Event event;
//     while (SDL_PollEvent(&event)) {
//         switch (event.type) {
//             case SDL_QUIT:
//                 // The user closed the window
//                 quit = 1;
//                 break;
//             case SDL_KEYDOWN:
//                 switch ( event.key.keysym.sym)
//                 {
//                 case SDLK_d:
//                     move_player(p, 10, 0);
//                     break;
//                 case SDLK_a:
//                     move_player(p, -10, 0);
//                     break;  
//                 case SDLK_w:
//                     move_player(p, 0, -10);
//                     break;
//                 case SDLK_s:
//                     move_player(p, 0, 10);
//                     break;


//                 }
//                 break;
//             case SDL_MOUSEBUTTONDOWN:
//                 // A mouse button was pressed
//                 break;
//             // Add more cases for other events as needed
//         }
//     }
// }





