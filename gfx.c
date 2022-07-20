#include "gfx.h"

void gfx_printScore(gfx_t *myGfx, game_t *myGame){
	char txt[100];
    	int score = myGame->board[myGame->marioIndex.y][myGame->marioIndex.x];
	sprintf(txt, "Score: %3d", score);
	myGfx->basicFont = TTF_OpenFont("./fonts/8bitOperatorPlus-Regular.ttf",32);
	//TTF_Font *our= TTF_OpenFont("/Users/pszymanski/Documents/Mario/fonts/8bitOperatorPlus-Regular.ttf", 2);
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
	// SDL_RenderClear(myGfx->renderer);

        // Render our text on a rectangle
        SDL_RenderCopy(myGfx->renderer,textureText,NULL,&rectangle);
}

 
void gfx_renderGhosts(game_t *myGame, gfx_t *myGfx){
	
	int n = myGame->ghost_num;	

	SDL_Rect rects[n];
	
	for(int i=0; i<n; i++){
		rects[i].x = myGame->ghostIndex[i].x*GFX_FIELD_SIZE;
		rects[i].y = myGame->ghostIndex[i].y*GFX_FIELD_SIZE;
		rects[i].w = 30;
		rects[i].h = 30;
		SDL_SetRenderDrawColor(myGfx->renderer,255,0,0,SDL_ALPHA_OPAQUE);
		//SDL_RenderFillRect(myGfx->renderer, &rects[i]);
		SDL_RenderCopy(myGfx->renderer, myGfx->myImgs.img_ghost, NULL, &rects[i]);
	}

}
