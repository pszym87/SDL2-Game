#include <SDL.h>
#include "logic.h"

void doKeyUp(game_t *g, SDL_Event *e);
void doKeyDown(game_t *g, SDL_Event *e);
void processEvents(game_t *myGame);
void processPlayModeInput(game_t *myGame);
void processStopModeInput(game_t *myGame);	
