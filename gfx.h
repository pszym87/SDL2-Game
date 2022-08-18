#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "logic.h"

#define GFX_FIELD_SIZE	30
#define WIN_H	(GFX_FIELD_SIZE*BSIZE_HEIGHT+SCORE_BAR_H)
#define WIN_W	(GFX_FIELD_SIZE*BSIZE_WIDTH)
#define SCORE_BAR_H	30
#define MARIO_VALUE	10

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

void gfx_initSDL(gfx_t *myGfx);

void gfx_playIntro(game_t *myGame, gfx_t *myGfx);

void gfx_showScene(SDL_Renderer *renderer);

void gfx_prepareScene(game_t *myGame, gfx_t *myGfx);

void gfx_intro(gfx_t *myGfx, game_t *myGame, int i);

void gfx_loadImgs(gfx_t *myGfx);

void gfx_printScore(gfx_t *myGfx, game_t *myGame);

void gfx_renderGhosts(game_t *myGame, gfx_t *myGfx);

void gfx_renderMario(game_t *myGame, gfx_t *myGfx);

void gfx_drawCircle(SDL_Renderer *renderer, int centreX, int centreY, int radius);

void gfx_printTheBoard(SDL_Renderer *renderer, SDL_Texture *image, int board[BSIZE_HEIGHT][BSIZE_WIDTH]);

void gfx_cleanupSDL(gfx_t *myGfx);


void gfx_endOfGame(gfx_t *myGfx, game_t *myGame);
