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
    SDL_Surface* image = SDL_LoadBMP(file_name_bmp);
    if(!image)
    {
      printf("Error loading image : %s",SDL_GetError());
      return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer,image);
    SDL_FreeSurface(image);

    if(NULL == texture)
    {
        fprintf(stderr, "Error loading texture : %s", SDL_GetError());
        return NULL;
    }
    SDL_QueryTexture(texture, NULL, NULL,size_w,size_h); 


    return texture;
}

void drawTexture (SDL_Renderer *gRenderer,SDL_Texture *texture,int x, int y , double angle)
{
    SDL_Rect position;
    position.x = x;
    position.y = y; 

    SDL_QueryTexture(texture,NULL,NULL,&position.w,&position.h);
	SDL_RenderCopyEx(gRenderer, texture, NULL, &position, angle, NULL, SDL_FLIP_NONE);
    //SDL_RenderCopy(gRenderer, texture, NULL, &position);

}

SDL_Texture* creerTextureSorbonne(SDL_Renderer *ecran,char *nom_file_bmp,int *size_w, int *size_h)
{
    SDL_Surface* image = SDL_LoadBMP(nom_file_bmp);
    if(!image)
    {
      printf("Erreur de chargement de l'image : %s",SDL_GetError());
      return NULL;
    }

    SDL_Texture* monImage = SDL_CreateTextureFromSurface(ecran,image);
    SDL_FreeSurface(image);

    if(NULL == monImage)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    SDL_QueryTexture(monImage, NULL, NULL,size_w,size_h); // on recup�re la taille de l'image


    return monImage;
}

void dessine_sorbonne(SDL_Renderer *ecran,SDL_Texture *sorbonneTexture,int x, int y)
{
    SDL_Rect position;
    position.x = x;
    position.y = y;

    SDL_QueryTexture(sorbonneTexture,NULL,NULL,&position.w,&position.h);// recupere la taille de l'image originelle
    SDL_RenderCopy(ecran, sorbonneTexture, NULL, &position);
}