#include "gfx.h"

void gfx_initSDL(gfx_t *myGfx){

	myGfx->window=NULL;
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not be initialized\n");
	SDL_GetError();
	}else{
		printf("SDL video system is ready to go\n");
	}

	TTF_Init();

	myGfx->basicFont = TTF_OpenFont("./fonts/8bitOperatorPlus-Regular.ttf",32);
	myGfx->window = SDL_CreateWindow("C SDL2 Window",20, 20, WIN_W,WIN_H,SDL_WINDOW_SHOWN);
	myGfx->renderer = NULL;
	myGfx->renderer = SDL_CreateRenderer(myGfx->window,-1,SDL_RENDERER_ACCELERATED);

	gfx_loadImgs(myGfx);
	
}

void gfx_playIntro(game_t *myGame, gfx_t *myGfx){
	for(int i=3; i>0; i--){
		gfx_prepareScene(myGame, myGfx);	
		gfx_intro(myGfx, myGame,i);
		gfx_showScene(myGfx->renderer);
		SDL_Delay(1000);
	}
}

void gfx_showScene(SDL_Renderer *renderer){
	SDL_RenderPresent(renderer);
}

void gfx_prepareScene(game_t *myGame, gfx_t *myGfx){

	SDL_SetRenderDrawColor(myGfx->renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);	
	SDL_RenderClear(myGfx->renderer);
	gfx_renderMario(myGame, myGfx);
	gfx_renderGhosts(myGame, myGfx);
	gfx_printTheBoard(myGfx->renderer, myGfx->myImgs.img_brick, myGame->board);
	gfx_printScore(myGfx,myGame);
}

void gfx_intro(gfx_t *myGfx, game_t *myGame, int i){
	char c[2];
	SDL_Delay(100);
	sprintf(c, "%d", i);

	SDL_Surface* surfaceText = TTF_RenderText_Solid(myGfx->basicFont,c,(SDL_Color){255,255,255,0});
		
	SDL_Texture* textureText = SDL_CreateTextureFromSurface(myGfx->renderer,surfaceText);

	SDL_FreeSurface(surfaceText); 

	SDL_Rect rectangle;
	rectangle.x=((WIN_W-160)/2);
	rectangle.y=((WIN_H-240)/2);
	rectangle.w=160;
	rectangle.h=240;

	SDL_SetRenderDrawColor(myGfx->renderer,0,0,0,SDL_ALPHA_OPAQUE);
	SDL_RenderCopy(myGfx->renderer,textureText,NULL,&rectangle);
	
}

void gfx_printScore(gfx_t *myGfx, game_t *myGame){
	char txt[100];
    	int score = myGame->board[myGame->marioIndex.y][myGame->marioIndex.x]-MARIO_VALUE;
	sprintf(txt, "Score: %3d", score);
	SDL_Surface* surfaceText = TTF_RenderText_Solid(myGfx->basicFont,txt,(SDL_Color){255,255,0,0});

    	SDL_Texture* textureText = SDL_CreateTextureFromSurface(myGfx->renderer,surfaceText);

	SDL_FreeSurface(surfaceText); 
    	
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

        SDL_RenderCopy(myGfx->renderer,textureText,NULL,&rectangle);
	
}


void gfx_endOfGame(gfx_t *myGfx, game_t *myGame){
	
	char c[100];
	const char *d = "Press <r> to restart";
	int score = myGame->board[myGame->marioIndex.y][myGame->marioIndex.x]-MARIO_VALUE;
	SDL_Delay(50);
	sprintf(c, "Your score:%d", score);
	SDL_Surface* surfaceText = TTF_RenderText_Solid(myGfx->basicFont,c,(SDL_Color){255,255,255,0});
	SDL_Surface* surfaceTextRestart = TTF_RenderText_Solid(myGfx->basicFont,d,(SDL_Color){255,204,0});

	SDL_Texture* textureText = SDL_CreateTextureFromSurface(myGfx->renderer,surfaceText);
	SDL_Texture* textureTextRestart = SDL_CreateTextureFromSurface(myGfx->renderer,surfaceTextRestart);
	
	SDL_FreeSurface(surfaceText); 
	SDL_FreeSurface(surfaceTextRestart); 

	SDL_Rect rectangle, rectangle2,backdrop;
	rectangle.x=20;
	rectangle.y=WIN_H/2-120;
	rectangle.w=500;
	rectangle.h=180;

	rectangle2.x=20;
	rectangle2.y=WIN_H/2+60;
	rectangle2.w = 300;
	rectangle2.h = 60;

	backdrop.x = 0;
	backdrop.y = WIN_H/2-140;
	backdrop.w = 560;
	backdrop.h = 300;

	SDL_SetRenderDrawColor(myGfx->renderer,0,0,0,100);
	SDL_RenderFillRect(myGfx->renderer, &backdrop);
	SDL_RenderCopy(myGfx->renderer,textureText,NULL,&rectangle);
	SDL_RenderCopy(myGfx->renderer,textureTextRestart,NULL,&rectangle2);

}
 
void gfx_renderGhosts(game_t *myGame, gfx_t *myGfx){
	
	SDL_Rect rects[myGame->ghost_num];
	
	for(int i=0; i<myGame->ghost_num; i++){
		rects[i].x = myGame->ghostIndex[i].x*GFX_FIELD_SIZE;
		rects[i].y = myGame->ghostIndex[i].y*GFX_FIELD_SIZE;
		rects[i].w = 30;
		rects[i].h = 30;
		SDL_RenderCopy(myGfx->renderer, myGfx->myImgs.img_ghost, NULL, &rects[i]);
	}

}

void gfx_renderMario(game_t *myGame, gfx_t *myGfx){
	
	SDL_Rect rect;
	
	rect.x = myGame->marioIndex.x*GFX_FIELD_SIZE;
	rect.y = myGame->marioIndex.y*GFX_FIELD_SIZE;
	rect.w = 30;
	rect.h = 30;
	
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
	
	SDL_FreeSurface(image);
	SDL_FreeSurface(img_mario);
	SDL_FreeSurface(img_ghost);
	
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

				}
				else if(board[i][j] == 0){
					
				}
			}
			
		} 
}

void gfx_cleanupSDL(gfx_t *myGfx){
	
	SDL_DestroyWindow(myGfx->window);
	
	SDL_DestroyTexture(myGfx->myImgs.img_mario);		
	SDL_DestroyTexture(myGfx->myImgs.img_ghost);		
	SDL_DestroyTexture(myGfx->myImgs.img_brick);		

	TTF_CloseFont(myGfx->basicFont);	
	
	IMG_Quit();
	SDL_Quit();
}
