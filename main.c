#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "./src/include/graphics.h"
#include "./src/include/player.h"
#include "./src/include/bullets.h"
#include "./src/include/zombies.h"
#include "./src/include/game_mechanics.h"
#include <SDL2/SDL.h>


int main(int argc, char* argv[])
{
    srand(time(NULL));
    // init window
    SDL_Window* fenetre=NULL;
    SDL_Renderer* ecran=NULL;
    init(&fenetre,&ecran,"ZombieZapper");

    // init player
    SDL_Texture* player_texture = loadTexture(ecran,"./textures/entities/player3.bmp",0,0);
    SDL_Texture* damaged_player_texture = loadTexture(ecran,"./textures/entities/damaged_player_2.bmp",0,0);
    player* p = create_player( 500 , 280 ,  player_health , player_texture );


    // init bullet
    SDL_Texture* bullet_texture = loadTexture(ecran,"./textures/entities/bullet.bmp",0,0);
    bullet_list* bl = NULL;

    // init zombied
    SDL_Texture* zombie_texture = loadTexture(ecran,"./textures/entities/zombie.bmp",0,0);
    zombie_list* zl = NULL;

    // init background
    SDL_Texture* background_texture = loadTexture(ecran,"./textures/background2.bmp",0,0);

    // init health bar
    SDL_Texture* health_bar_texture = loadTexture(ecran,"./textures/healthbar/1_heart.bmp",0,0);
    SDL_Texture* health_bar_texture2 = loadTexture(ecran,"./textures/healthbar/2_hearts.bmp",0,0);
    SDL_Texture* health_bar_texture3 = loadTexture(ecran,"./textures/healthbar/3_hearts.bmp",0,0);
    SDL_Texture* current_health_bar_texture = health_bar_texture;

    // init menu
    SDL_Texture* main_menu_texture = loadTexture(ecran,"./textures/menus/menu.bmp",0,0);

    // init gameover_screen
    SDL_Texture* gameover_screen_texture = loadTexture(ecran,"./textures/menus/GameOverScreen_white.bmp",0,0);

    // init how to play screen
    SDL_Texture* how_to_play_screen_texture = loadTexture(ecran,"./textures/menus/how_to_play.bmp",0,0);

    // init mouse
    int mouseX, mouseY;
    Uint32 mouseState;
    SDL_Event event;

    // init score textures
    SDL_Texture** score_textures = malloc(10*sizeof(SDL_Texture*));
    score_textures[0] = loadTexture(ecran,"./textures/digits/digit_0.bmp",0,0);
    score_textures[1] = loadTexture(ecran,"./textures/digits/digit_1.bmp",0,0);
    score_textures[2] = loadTexture(ecran,"./textures/digits/digit_2.bmp",0,0);
    score_textures[3] = loadTexture(ecran,"./textures/digits/digit_3.bmp",0,0);
    score_textures[4] = loadTexture(ecran,"./textures/digits/digit_4.bmp",0,0);
    score_textures[5] = loadTexture(ecran,"./textures/digits/digit_5.bmp",0,0);
    score_textures[6] = loadTexture(ecran,"./textures/digits/digit_6.bmp",0,0);
    score_textures[7] = loadTexture(ecran,"./textures/digits/digit_7.bmp",0,0);
    score_textures[8] = loadTexture(ecran,"./textures/digits/digit_8.bmp",0,0);
    score_textures[9] = loadTexture(ecran,"./textures/digits/digit_9.bmp",0,0);
    SDL_Texture* score_texture = loadTexture(ecran,"./textures/digits/score.bmp",0,0);
    int score = 0 ;
    int highscore = 0;
    loadHighScore( "./src/highscore.txt", &highscore) ;
    printf("highscore : %d" , highscore);

    int reintialize = 0;
    int quit = 0 ;
    int  scene_manager = 0;

    while ( quit == 0)
    {
        SDL_RenderClear(ecran);

        switch (scene_manager) {

            case 0 :
                drawTexture(ecran,main_menu_texture,0,0,0);
                score_update(highscore,ecran, score_textures , highscore_menu_x , highscore_menu_y);
                buttons_manager ( mouseState , event  , &quit , &scene_manager , &reintialize, &mouseX , &mouseY) ;
                break;
            case 1 :
                if ( reintialize == 1 ) {
                    free_all(&bl , &zl) ;
                    score = 0 ;
                    p -> health = player_health;
                    p -> taking_damage = 0 ;
                    p->x = 500;
                    p->y = 280;
                    p->rect.x = p->x;
                    p->rect.y = p->y;
                    reintialize = 0 ;
                }
                current_health_bar_texture = health_manager(p, &scene_manager , health_bar_texture,health_bar_texture2,health_bar_texture3);
                input_player(p , &quit);
                rotate_player(p);
                zombie_generator(&zl , zombie_texture , spawn_probability , score , difficulty_multiplier_spawn) ;
                move_zombies(&zl , p , score , difficulty_multiplier_speed);
                shoot_checker(p,&bl,bullet_texture);
                move_bullets(&bl);
                collision_manager(p,&bl,&zl, &score);
                damage_animation(p, player_texture , damaged_player_texture);
                drawTexture(ecran,background_texture,0,0,0);
                score_update(score,ecran,score_textures , score_value_x , score_value_y);
                frame_drawer(ecran,p,zl,bl,current_health_bar_texture , score_texture);
                break;
            case 2 :
                // game over
                saveHighScore( "./src/highscore.txt" , score) ;
                loadHighScore( "highscore.txt" , &highscore) ;
                drawTexture(ecran,gameover_screen_texture,0,0,0);
                score_update(highscore,ecran,score_textures,highscore_gameover_x , highscore_gameover_y);
                score_update(score,ecran,score_textures,score_gameover_x , score_gameover_y);
                buttons_manager ( mouseState , event  , &quit , &scene_manager , &reintialize, &mouseX , &mouseY) ;
                break;
            case 3 :
                drawTexture(ecran,how_to_play_screen_texture,0,0,0);
                buttons_manager ( mouseState , event  , &quit , &scene_manager, &reintialize , &mouseX , &mouseY) ;
                break;
        }
        SDL_RenderPresent(ecran);
    }
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
    if ( score_textures[0] ) { SDL_DestroyTexture(score_textures[0]); score_textures[0] = NULL; }
    if ( score_textures[1] ) { SDL_DestroyTexture(score_textures[1]); score_textures[1] = NULL; }
    if ( score_textures[2] ) { SDL_DestroyTexture(score_textures[2]); score_textures[2] = NULL; }
    if ( score_textures[3] ) { SDL_DestroyTexture(score_textures[3]); score_textures[3] = NULL; }
    if ( score_textures[4] ) { SDL_DestroyTexture(score_textures[4]); score_textures[4] = NULL; }
    if ( score_textures[5] ) { SDL_DestroyTexture(score_textures[5]); score_textures[5] = NULL; }
    if ( score_textures[6] ) { SDL_DestroyTexture(score_textures[6]); score_textures[6] = NULL; }
    if ( score_textures[7] ) { SDL_DestroyTexture(score_textures[7]); score_textures[7] = NULL; }
    if ( score_textures[8] ) { SDL_DestroyTexture(score_textures[8]); score_textures[8] = NULL; }
    if ( score_textures[9] ) { SDL_DestroyTexture(score_textures[9]); score_textures[9] = NULL; }

    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    free( p -> texture );
    free( p );
    free_all(&bl,&zl);

    close(&fenetre,&ecran);

    return 0;
}
