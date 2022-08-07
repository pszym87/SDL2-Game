/*
Build with: 
clang main.c logic.c gfx.c diagnostics.c ctrl.c adj.c -L/opt/homebrew/lib -lSDL2 -L/opt/homebrew/Cellar/sdl2_ttf/HEAD-b35c03d_1/lib -lSDL2_ttf -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/Cellar/sdl2_image/2.0.5/lib -lSDL2_image 
*/
#include "logic.h"
#include <SDL.h>
#include <SDL_image.h>
#include "gfx.h"
#include "diagnostics.h"
#include "ctrl.h"

int main(){
 	
	// init a game
	game_t myGame;
	gfx_t myGfx;

	gameInit(&myGame, 3);	
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
		
			moveGhosts(&myGame);
			processPlayModeInput(&myGame);
			movePlayer(&myGame);			

			gfx_prepareScene(&myGame, &myGfx);	
			gfx_showScene(myGfx.renderer);

			SDL_Delay(90);

		}else if(myGame.gameStatus == SSTOP){	

			processStopModeInput(&myGame);

		}

    	}
	gfx_cleanupSDL(&myGfx);

}

	



