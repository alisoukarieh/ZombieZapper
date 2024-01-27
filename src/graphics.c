#include "./include/graphics.h"

// Init SDL
int init(SDL_Window** gWindow,SDL_Renderer** gRenderer, char* nameWindow)
{
	//Initialization flag
	int success = TRUE;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = FALSE;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		*gWindow = SDL_CreateWindow(nameWindow, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( *gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = FALSE;
		}
		else
		{
			//Create vsynced renderer for window
			*gRenderer = SDL_CreateRenderer( *gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( *gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = FALSE;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( *gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	return success;
}

// Close SDL
void close(SDL_Window** gWindow,SDL_Renderer** gRenderer)
{
	//Destroy window
	SDL_DestroyRenderer( *gRenderer );
	SDL_DestroyWindow(* gWindow );
	*gWindow = NULL;
	*gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

// Return a SDL_Texture from a file
SDL_Texture* loadTexture(SDL_Renderer *gRenderer,char *file_name_bmp,int *size_w, int *size_h)
{
    SDL_Surface* image = SDL_LoadBMP(file_name_bmp); // load image
    if(!image)
    {
      printf("Error loading image : %s",SDL_GetError());
      return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer,image); // create texture from image
    SDL_FreeSurface(image);

    if(NULL == texture)
    {
        fprintf(stderr, "Error loading texture : %s", SDL_GetError());
        return NULL;
    }
    SDL_QueryTexture(texture, NULL, NULL,size_w,size_h);
    return texture;
}

// Draw a SDL_Texture at position x, y
void drawTexture (SDL_Renderer *gRenderer,SDL_Texture *texture,int x, int y , double angle)
{
    SDL_Rect position;
    position.x = x;
    position.y = y;

    SDL_QueryTexture(texture,NULL,NULL,&position.w,&position.h);
	SDL_RenderCopyEx(gRenderer, texture, NULL, &position, angle, NULL, SDL_FLIP_NONE);
}

// Initialize digits textures
void score_init(SDL_Renderer* renderer , SDL_Texture** digits){
	for (int i = 0; i < 10; i++) {
		char filename[256];
		sprintf(filename, "/Users/souka/Desktop/L2/Advanced_C/ZombieZapper/textures/digits/digit_%d.bmp", i);
		digits[i] = loadTexture(renderer , filename , 0 , 0 ); // Load digit texture in array of textures
	}
}

//Draw digit textures corresponding to the score
void score_update(int score, SDL_Renderer* renderer, SDL_Texture** digits , int x , int y) {
	char score_str[10];
    sprintf(score_str, "%d", score); // Convert score to string
    int digit_width = 30; // Assumes each digit texture is 32 pixels wide
    int digit_padding = 0; // Padding between digits
    for (int i = 0; i < strlen(score_str); i++) {
        char c = score_str[i];
        int digit = c - '0'; // Convert character to digit value
		drawTexture(renderer, digits[digit], x + i * (digit_width + digit_padding), y, 0);
    }
}

// Draw all textures that make a frame
void frame_drawer( SDL_Renderer* renderer , player* p , zombie_list* zl , bullet_list* bl , SDL_Texture* health_texture , SDL_Texture* score_texture){
    drawTexture(renderer , p->texture , p->x , p->y , p->angle);
    drawTexture(renderer , score_texture , score_x , score_y, 0);
    drawTexture(renderer , health_texture , HEALTH_BAR_X , HEALTH_BAR_Y, 0);
    zombie_list* tmp = zl;
    while (tmp != NULL){ // draw all zombies of a list
        drawTexture(renderer , tmp->zombie->texture , tmp->zombie->x , tmp->zombie->y , tmp->zombie->angle);
        tmp = tmp->next;
    }
    bullet_list* tmp2 = bl;
    while (tmp2 != NULL){ // draw all bullets of a list
        drawTexture(renderer , tmp2->bullet->texture , tmp2->bullet->x , tmp2->bullet->y , tmp2->bullet->angle);
        tmp2 = tmp2->next;
    }
    SDL_RenderPresent(renderer);
}

// Change player textures to make damage animation
void damage_animation( player* p , SDL_Texture* normal_player , SDL_Texture* damaged_player ){
    if ( p->taking_damage != 0 ){
        if (p->taking_damage % 5 == 0) { // frame delay
            if (p->texture == normal_player){
                p->texture = damaged_player;
            } else {
                p->texture = normal_player;
            }
        }
        p->taking_damage -= 1;
    } else {
        p->texture = normal_player;
    }
}
