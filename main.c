/*
Build with: 
clang main.c logic.c gfx.c ctrl.c adj.c -L/opt/homebrew/lib -lSDL2 -L/opt/homebrew/Cellar/sdl2_ttf/HEAD-b35c03d_1/lib -lSDL2_ttf -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/Cellar/sdl2_image/2.0.5/lib -lSDL2_image 
*/
#include "logic.h"
#include <SDL.h>
#include <SDL_image.h>
#include "gfx.h"
#include "ctrl.h"
#include <pthread.h>

int main(){
 	
	// init a game
	game_t myGame;
	gfx_t myGfx;

	gameInit(&myGame, NGHOSTS);	
	gfx_initSDL(&myGfx);	

	// game loop
	while(1){
		
		// intercept keyboard events and propagate them to
		// the main structure of the game
		processEvents(&myGame);	
		

		// 3.. 2.. 1.. START!
		if(myGame.gameStatus == SINTRO){	
			gfx_playIntro(&myGame, &myGfx);
			myGame.gameStatus = SPLAY;
		}
		
		// Actual game
		else if(myGame.gameStatus == SPLAY){
			
			// apply previously generated moves into the board
			moveGhosts(&myGame);

			// player's move
			processPlayModeInput(&myGame);
			movePlayer(&myGame);			

			// The main "thread" renders a scene
			// In order to save time (and maintain FPS),
			// calculate next moves of the figures in a separate thread  
			pthread_t genMvTh;
			pthread_create(&genMvTh, NULL, genMovesForGhosts, &myGame);
			
			// render a scene
			gfx_prepareScene(&myGame, &myGfx);	
			gfx_showScene(myGfx.renderer);

			SDL_Delay(90);

			pthread_join(genMvTh, NULL);


		// Stop the game and show the final score
		}else if(myGame.gameStatus == SSTOP){	
			processStopModeInput(&myGame);	
			gfx_prepareScene(&myGame, &myGfx);
			gfx_endOfGame(&myGfx, &myGame);
			gfx_showScene(myGfx.renderer);
		}

    	}
	gfx_cleanupSDL(&myGfx);

}

	



