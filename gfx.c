#include "gfx.h"


void gfx_intro(gfx_t *myGfx, game_t *myGame, int i){
	char c[2];
	SDL_Delay(100);
	sprintf(c, "%d", i);
	TTF_Font *font = TTF_OpenFont("./fonts/8bitOperatorPlus-Regular.ttf",72);
	//TTF_Font *our= TTF_OpenFont("/Users/pszymanski/Documents/Mario/fonts/8bitOperatorPlus-Regular.ttf", 2);
	SDL_Surface* surfaceText = TTF_RenderText_Solid(font,c,(SDL_Color){255,255,255,0});
		
	// Setup the texture
	SDL_Texture* textureText = SDL_CreateTextureFromSurface(myGfx->renderer,surfaceText);

	SDL_FreeSurface(surfaceText); 

	// Create a rectangle to draw on

	SDL_Rect rectangle;

	rectangle.x=((WIN_W-160)/2);
	rectangle.y=((WIN_H-240)/2);
	rectangle.w=160;
	rectangle.h=240;

	SDL_SetRenderDrawColor(myGfx->renderer,0,0,0,SDL_ALPHA_OPAQUE);
	//SDL_RenderFillRect(myGfx->renderer, &backdrop);
	// SDL_RenderClear(myGfx->renderer);

	// Render our text on a rectangle
	SDL_RenderCopy(myGfx->renderer,textureText,NULL,&rectangle);
	
}

void gfx_printScore(gfx_t *myGfx, game_t *myGame){
	char txt[100];
    	int score = myGame->board[myGame->marioIndex.y][myGame->marioIndex.x]-MARIO_VALUE;
	sprintf(txt, "Score: %3d", score);
	myGfx->basicFont = TTF_OpenFont("./fonts/8bitOperatorPlus-Regular.ttf",20);
	//TTF_Font *our= TTF_OpenFont("/Users/pszymanski/Documents/Mario/fonts/8bitOperatorPlus-Regular.ttf", 2);
	SDL_Surface* surfaceText = TTF_RenderText_Solid(myGfx->basicFont,txt,(SDL_Color){255,255,0,0});


    	// Setup the texture
    	SDL_Texture* textureText = SDL_CreateTextureFromSurface(myGfx->renderer,surfaceText);

	SDL_FreeSurface(surfaceText); 
    	
	// Create a rectangle to draw on
    	SDL_Rect backdrop, rectangle;
    	backdrop.x = 0;
    	backdrop.y = WIN_H-SCORE_BAR_H;
    	backdrop.w = WIN_W;
    	backdrop.h = SCORE_BAR_H;

	rectangle.x=10;
	rectangle.y=WIN_H-SCORE_BAR_H+10;
	rectangle.w=120;
	rectangle.h=SCORE_BAR_H - 12;

	SDL_SetRenderDrawColor(myGfx->renderer,0,0,0,SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(myGfx->renderer, &backdrop);
	// SDL_RenderClear(myGfx->renderer);

        // Render our text on a rectangle
        SDL_RenderCopy(myGfx->renderer,textureText,NULL,&rectangle);
}

 
void gfx_renderGhosts(game_t *myGame, gfx_t *myGfx){
	
	SDL_Rect rects[myGame->ghost_num];
	
	for(int i=0; i<myGame->ghost_num; i++){
		rects[i].x = myGame->ghostIndex[i].x*GFX_FIELD_SIZE;
		rects[i].y = myGame->ghostIndex[i].y*GFX_FIELD_SIZE;
		rects[i].w = 30;
		rects[i].h = 30;
		//SDL_SetRenderDrawColor(myGfx->renderer,255,0,0,SDL_ALPHA_OPAQUE);
		//SDL_RenderFillRect(myGfx->renderer, &rects[i]);
		SDL_RenderCopy(myGfx->renderer, myGfx->myImgs.img_ghost, NULL, &rects[i]);
	}

}

void gfx_renderMario(game_t *myGame, gfx_t *myGfx){
	
	SDL_Rect rect;
	
	rect.x = myGame->marioIndex.x*GFX_FIELD_SIZE;
	rect.y = myGame->marioIndex.y*GFX_FIELD_SIZE;
	rect.w = 30;
	rect.h = 30;
	//SDL_SetRenderDrawColor(myGfx->renderer,255,0,0,SDL_ALPHA_OPAQUE);
	
	SDL_RenderCopy(myGfx->renderer, myGfx->myImgs.img_mario, NULL, &rect);
	

}

void gfx_loadImgs(gfx_t *myGfx){
		
	int flags = IMG_INIT_PNG;
	int initStatus = IMG_Init(flags);

	if((initStatus & flags) != flags){
		printf("SDL2_Image format not available\n");
	}
	
	SDL_Surface* image;
	SDL_Surface *img_mario, *img_ghost;
	image = IMG_Load("./images/brick.png");
	img_mario = IMG_Load("./images/mario.png");
	img_ghost = IMG_Load("./images/ghost.png");
	if(!image){
		printf("Image not loaded...");
	}

	SDL_Texture* ourPNG = SDL_CreateTextureFromSurface(myGfx->renderer, image);
	SDL_Texture *marioPNG = SDL_CreateTextureFromSurface(myGfx->renderer, img_mario); 
	SDL_Texture *ghostPNG = SDL_CreateTextureFromSurface(myGfx->renderer, img_ghost);

	myGfx->myImgs = (gfx_imgs_t){marioPNG, ghostPNG, ourPNG};
}

void gfx_drawCircle(SDL_Renderer* renderer, int centreX, int centreY, int radius)
{
   const int diameter = (radius * 2);

   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}


void gfx_printTheBoard(SDL_Renderer *renderer, SDL_Texture *image, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
	SDL_Rect rec;
	for(int i=0; i<BSIZE_HEIGHT; i++){
		for(int j=0; j<BSIZE_WIDTH; j++){
				if(board[i][j] ==-1){
					rec.x = j*GFX_FIELD_SIZE;
					rec.y = i*GFX_FIELD_SIZE;
					rec.w = GFX_FIELD_SIZE;
					rec.h = GFX_FIELD_SIZE;
					SDL_RenderCopy(renderer,image,NULL,&rec);
					
				}
				else if(board[i][j] == 1){
					
					SDL_SetRenderDrawColor(renderer, 255,255,0,SDL_ALPHA_OPAQUE);
					SDL_RenderDrawPoint(renderer,(j*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2)-1, i*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2);	
					SDL_RenderDrawPoint(renderer,(j*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2)+1, i*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2);
					SDL_RenderDrawPoint(renderer,j*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2, (i*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2)-1);
					SDL_RenderDrawPoint(renderer,j*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2, (i*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2)+1);
					SDL_RenderDrawPoint(renderer,j*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2, i*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2);
					//SDL_RenderDrawPoint(renderer,j*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2, i*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2);

					//gfx_drawCircle(renderer,j*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2, i*GFX_FIELD_SIZE+GFX_FIELD_SIZE/2,1); 				
				}
				else if(board[i][j] == 0){
					
				}
			}
			
		} 
}
/*
void gfx_eventLoopPlayMode(SDL_Event *event){
	while(SDL_PollEvent(event)){
		    
			if(event->key.keysym.sym == SDLK_UP){ 
				move = MV_UP;
			}
			if(event->key.keysym.sym == SDLK_DOWN)
				move = MV_DOWN;
			if(event->key.keysym.sym == SDLK_LEFT)
				move = MV_LEFT; 
			if(event->key.keysym.sym == SDLK_RIGHT) 
				move = MV_RIGHT;
		
	 
		    	if(event->type == SDL_QUIT){
				gameIsRunning= false;
		    	}	

		}
}*/
