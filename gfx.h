#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "logic.h"

typedef struct gfx_s{
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font *basicFont;	
} gfx_t;

void gfx_printScore(gfx_t *myGfx, game_t *myGame);
