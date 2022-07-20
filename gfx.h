#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "logic.h"

#define GFX_FIELD_SIZE	30

typedef struct gfx_imgs_s{
	SDL_Texture *img_mario;
	SDL_Texture *img_ghost;
	SDL_Texture *img_brick;
} gfx_imgs_t;

typedef struct gfx_s{
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font *basicFont;
	gfx_imgs_t myImgs;	
} gfx_t;


void gfx_printScore(gfx_t *myGfx, game_t *myGame);

void gfx_renderGhosts(game_t *myGame, gfx_t *myGfx);
