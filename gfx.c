#include "gfx.h"

void gfx_printScore(gfx_t *myGfx, game_t *myGame){
	char txt[100];
    	int score = myGame->board[myGame->marioIndex.y][myGame->marioIndex.x];
	sprintf(txt, "Score: %3d", score);
	myGfx->basicFont = TTF_OpenFont("./fonts/8bitOperatorPlus-Regular.ttf",32);
	TTF_Font *our= TTF_OpenFont("/Users/pszymanski/Documents/ANSI\ C/MarioGame/logic/fonts/8bitOperatorPlus-Regular.ttf", 32);
	SDL_Surface* surfaceText = TTF_RenderText_Solid(myGfx->basicFont,txt,(SDL_Color){255,255,255,0});


    	// Setup the texture
    	SDL_Texture* textureText = SDL_CreateTextureFromSurface(myGfx->renderer,surfaceText);

	SDL_FreeSurface(surfaceText); 
    	
	// Create a rectangle to draw on
    	SDL_Rect rectangle;
    	rectangle.x = 10;
    	rectangle.y = 10;
    	rectangle.w = 400;
    	rectangle.h = 100;


	SDL_SetRenderDrawColor(myGfx->renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
	//SDL_RenderFillRect(myGfx->renderer, &rectangle);
 //       SDL_RenderClear(myGfx.renderer);

        // Render our text on a rectangle
        SDL_RenderCopy(myGfx->renderer,textureText,NULL,&rectangle);
} 
