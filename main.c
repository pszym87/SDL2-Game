/*
Build with: 
clang main.c logic.c gfx.c diagnostics.c -L/opt/homebrew/lib -lSDL2 -L/opt/homebrew/Cellar/sdl2_ttf/HEAD-b35c03d_1/lib -lSDL2_ttf -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/Cellar/sdl2_image/2.0.5/lib -lSDL2_image 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include "gfx.h"
#include "diagnostics.h"


//gfx
void gfx_printTheBoard(SDL_Renderer *renderer, SDL_Texture *image, int[BSIZE_HEIGHT][BSIZE_WIDTH]);

void doKeyUp(game_t *g, SDL_Event *e);
void doKeyDown(game_t *g, SDL_Event *e);
int main(){
 	

	game_t myGame;
	gfx_t myGfx;

	gameInit(&myGame, 3);	
    	myGfx.window=NULL;

    	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not be initialized\n");
	SDL_GetError();
    	}else{
		printf("SDL video system is ready to go\n");
    	}

	TTF_Init();

    	myGfx.window = SDL_CreateWindow("C SDL2 Window",20, 20, WIN_W,WIN_H,SDL_WINDOW_SHOWN);
    	myGfx.renderer = NULL;
    	myGfx.renderer = SDL_CreateRenderer(myGfx.window,-1,SDL_RENDERER_ACCELERATED);

	gfx_loadImgs(&myGfx);
	

    	bool gameIsRunning = true;
    	
    	uint32_t startT = SDL_GetTicks();

	index_t move = (index_t){0,0}; 
	int intro=0;
  	int intro_i=3;
	
	
	while(gameIsRunning){
		SDL_Event event;

		while(SDL_PollEvent(&event)){
		   
			switch(event.type){
				case SDL_QUIT:
					exit(0);
					break;

				case SDL_KEYDOWN:
					doKeyDown(&myGame, &event);
					break;				

				case SDL_KEYUP:
					doKeyUp(&myGame, &event);
					break;
			} 
		}
		
		if(myGame.gameStatus == SINTRO){
				
			SDL_SetRenderDrawColor(myGfx.renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);	
			SDL_RenderClear(myGfx.renderer);
			gfx_renderMario(&myGame, &myGfx);
			gfx_renderGhosts(&myGame, &myGfx);
			gfx_printTheBoard(myGfx.renderer, myGfx.myImgs.img_brick, myGame.board);
			gfx_printScore(&myGfx,&myGame); // <--- printScore();

			SDL_SetRenderDrawColor(myGfx.renderer, 255,255,0,255);
			SDL_RenderDrawPoint(myGfx.renderer, 100,100);	
		
			gfx_intro(&myGfx, &myGame,intro_i);
			SDL_RenderPresent(myGfx.renderer);
			
			if(SDL_GetTicks() - intro >1000){
				intro = SDL_GetTicks();		
				if(intro_i-- <=1) {
					myGame.gameStatus = SPLAY;
					intro = 0;
					intro_i = 3;
				}	
			}
				
		}
		
		else if(myGame.gameStatus == SPLAY){
		
			if(myGame.keyb[SDL_SCANCODE_UP] == 1) move = MV_UP;
			else if(myGame.keyb[SDL_SCANCODE_DOWN] == 1) move = MV_DOWN;
			else if(myGame.keyb[SDL_SCANCODE_LEFT] == 1) move = MV_LEFT;
			else if(myGame.keyb[SDL_SCANCODE_RIGHT] == 1) move = MV_RIGHT;
		
		if(SDL_GetTicks() - startT>120){
			srand(time(0));
			index_t move2 = generateRandomPossibleMove(myGame.ghostIndex, myGame.board);	
			index_t move3 = generateRandomPossibleMove(myGame.ghostIndex+1, myGame.board);
			index_t move4 = generateRandomPossibleMove(myGame.ghostIndex+2, myGame.board);
			moveRespectingRules(move2,&myGame,0);
			moveRespectingRules(move3, &myGame, 1);
			moveRespectingRules(move4, &myGame, 2);
			moveRespectingRules_new(move, &myGame);	
			
			SDL_SetRenderDrawColor(myGfx.renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);	
			SDL_RenderClear(myGfx.renderer);
			gfx_renderMario(&myGame, &myGfx);
			gfx_renderGhosts(&myGame, &myGfx);
			gfx_printTheBoard(myGfx.renderer, myGfx.myImgs.img_brick, myGame.board);
			gfx_printScore(&myGfx,&myGame); // <--- printScore();

			SDL_SetRenderDrawColor(myGfx.renderer, 255,255,0,255);
			SDL_RenderDrawPoint(myGfx.renderer, 100,100);	
			SDL_RenderPresent(myGfx.renderer);
			startT = SDL_GetTicks();
			move = (index_t) {0,0};
			printTheBoard(myGame.board);
	}
	} else if(myGame.gameStatus == SSTOP){
	
		if(myGame.keyb[SDL_SCANCODE_R] == 1){
			gameInit(&myGame, 3);	
			myGame.gameStatus = SINTRO;
		};
	
		//SDL_Event e;
		//int i = SDL_PollEvent(&e);
		//SDL_Delay(200);	
		//printf("kjkl");
	}

    }

	SDL_DestroyWindow(myGfx.window);
   	//SDL_FreeSurface(image); <-- dodaj poprawne niszczenie obiektow
    	//SDL_DestroyTexture(ourPNG);
    	IMG_Quit();
    	SDL_Quit();

}

	

void scanKey(){

}

void doKeyUp(game_t *g, SDL_Event *e){
	if(e->key.repeat == 0 && e->key.keysym.scancode < KEYB_LEN)
		g->keyb[e->key.keysym.scancode] = 0;
}

void doKeyDown(game_t *g, SDL_Event *e){
	if(e->key.repeat == 0 && e->key.keysym.scancode < KEYB_LEN)
		g->keyb[e->key.keysym.scancode] = 1;
}

