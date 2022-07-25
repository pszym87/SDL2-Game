#include "ctrl.h"
#include <SDL.h>

void doKeyUp(game_t *g, SDL_Event *e){
	if(e->key.repeat == 0 && e->key.keysym.scancode < KEYB_LEN)
		g->keyb[e->key.keysym.scancode] = 0;
}

void doKeyDown(game_t *g, SDL_Event *e){
	if(e->key.repeat == 0 && e->key.keysym.scancode < KEYB_LEN)
		g->keyb[e->key.keysym.scancode] = 1;
}


void processEvents(game_t *myGame){
	SDL_Event event;

	while(SDL_PollEvent(&event)){
	   
		switch(event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				doKeyDown(myGame, &event);
				break;				

			case SDL_KEYUP:
				doKeyUp(myGame, &event);
				break;
		}
	} 
}

void processPlayModeInput(game_t *myGame){
	if(myGame->keyb[SDL_SCANCODE_UP] == 1) myGame->playerMove = MV_UP;
	else if(myGame->keyb[SDL_SCANCODE_DOWN] == 1) myGame->playerMove = MV_DOWN;
	else if(myGame->keyb[SDL_SCANCODE_LEFT] == 1) myGame->playerMove = MV_LEFT;
	else if(myGame->keyb[SDL_SCANCODE_RIGHT] == 1) myGame->playerMove = MV_RIGHT;
}


void processStopModeInput(game_t *myGame){	
	if(myGame->keyb[SDL_SCANCODE_R] == 1){
		gameInit(myGame, 3);	
		myGame->gameStatus = SINTRO;
	};	
}
