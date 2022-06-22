/*
Build with: 
clang main.c logic.c -L/opt/homebrew/lib -lSDL2 -L/opt/homebrew/Cellar/sdl2_ttf/HEAD-b35c03d_1/lib -lSDL2_ttf -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/Cellar/sdl2_image/2.0.5/lib -lSDL2_image 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <math.h>

#define ASC_UP			'i'
#define ASC_DOWN		'k'
#define ASC_LEFT		'j'
#define ASC_RIGHT		'l'


// KOMENTARZ #1
// chcialbym to jeszcze zakodowac na wskaznikach wielowymiarowych (podwojnych) - zeby to sobie dobrze przecwiczyc

// KOMENTAZR #2
// chcialbym to jeszcze zakodowac z uzyciem wyrazenia regularnego ? (expression)
// nie mozna miec w ternary operatorze returna

void printTheBoard(int[BSIZE_HEIGHT][BSIZE_WIDTH]);
void printIndexPosition(index_t);
void twoPlayersPlay(index_t*, index_t*, int[BSIZE_HEIGHT][BSIZE_WIDTH]);
void onePlayerPlay(index_t*, index_t*, int[BSIZE_HEIGHT][BSIZE_WIDTH]);

typedef struct game{
	int board[BSIZE_HEIGHT][BSIZE_WIDTH];
	index_t marioIndex;
	index_t	ghostIndex;
} t_game;


int main(){
	
	t_game myGame ={{
	{ -1 ,  1 ,  10, -1 , 1 , 1 , 1 , 1 }, 
	{  1 , -1 ,  1 , -1 , 1 , -1,-1 , 1 }, 
	{  4 ,  1 ,  1 ,  1 ,-1 , 1 , 1 , 1 },
	{  0 , -1 , -1 , -1 , 1 , -1, -1, 1 }
	},{0,0},{0,0}}; 
	myGame.marioIndex = getAnIndexPositionOf(10,myGame.board);
	myGame.ghostIndex = getAnIndexPositionOf(4,myGame.board);
	

	
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=NULL;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
	printf("SDL could not be initialized\n");
	SDL_GetError();
    }else{
	printf("SDL video system is ready to go\n");
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window",20, 20, 640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // Setup and initialize the SDL2_Image library
    // with our supported formats
    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if((initStatus & flags) != flags){
	printf("SDL2_Image format not available\n");
    }

    SDL_Surface* image;
    image = IMG_Load("./images/mario.png");
    if(!image){
	printf("Image not loaded...");
    }

    SDL_Texture* ourPNG = SDL_CreateTextureFromSurface(renderer, image);

    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
	SDL_Event event;

	// (1) Handle Input
	// Start our event loop
	while(SDL_PollEvent(&event)){
	    // Handle each specific event
	    if(event.type == SDL_QUIT){
		gameIsRunning= false;
	    }

	}
	// (2) Handle Updates
	
	// (3) Clear and Draw the Screen
	// Gives us a clear "canvas"
	SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer,ourPNG,NULL,NULL);

	// Finally show what we've drawn
	SDL_RenderPresent(renderer);
    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // Free our png image surface
    SDL_FreeSurface(image);
    // And destroy our texture
    SDL_DestroyTexture(ourPNG);

    IMG_Quit();

    // Quit our program.
    SDL_Quit();


	printIndexPosition(myGame.marioIndex);
	printIndexPosition(myGame.ghostIndex);
	printTheBoard(myGame.board);
	onePlayerPlay(&myGame.marioIndex, &myGame.ghostIndex, myGame.board);
}
 
void printTheBoard(int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
	
	printf("\n\n=== The board ===\n\n"); 	

	for(int i=0; i<BSIZE_HEIGHT; i++){
		for(int j=0; j<BSIZE_WIDTH; j++){
			printf("%3d\t", board[i][j]);
		} 
		printf("\n");
	}

}


/**
 * \brief Do przeniesienia do pliku z widokiem
 *        Sluzy do diagnostyki gry. Drukuje na ekranie podane koordynaty.
 *
 * \param position Koordynaty x,y
 */

void printIndexPosition(index_t position){
	printf("\nIndex position y=%d, x=%d\n", position.y, position.x);
}


void twoPlayersPlay(index_t *marioIndex, index_t *ghostIndex, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){

	char c;
	index_t move;
	int zmianaFigury = 0;
	while(c!='q'){
		printf("Wprowadz ruch dla %s\n", (zmianaFigury%2 == 0) ? "Mario" : "Duszka");
		scanf("%c", &c);
		switch(c){
			case ASC_UP:
				move = MV_UP;
				break;

			case ASC_DOWN:
				move = MV_DOWN;
				break;
			case ASC_LEFT:
				move = MV_LEFT;
				break;

			case ASC_RIGHT:
				move = MV_RIGHT;
				break;
		}
		if(zmianaFigury++%2 == 0){
			printf("Ruch Mario: \n");
			moveRespectingRules(move, marioIndex, board);
		} else{
			printf("Ruch Duszka: \n");
			moveRespectingRules(move, ghostIndex, board);
		}
		
		printTheBoard(board);
		scanf("%c", &c);
		printf("Nacisnieto: %c", c);
	
	}
}

void onePlayerPlay(index_t *marioIndex, index_t *ghostIndex, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
		
	char c;
	srand(time(0));
	index_t move;
	int zmianaFigury = 0;

	while(c!='q'){
		if(zmianaFigury%2 == 0){
			printf("Wprowadz ruch dla Mario:\n");
			scanf("%c", &c);
			fflush(stdin);
			zmianaFigury++;
			switch(c){
				case ASC_UP:
					move = MV_UP;
					break;

				case ASC_DOWN:
					move = MV_DOWN;
					break;
				case ASC_LEFT:
					move = MV_LEFT;
					break;

				case ASC_RIGHT:
					move = MV_RIGHT;
					break;
			}
			moveRespectingRules(move, marioIndex, board);
		}else{
			zmianaFigury++;
			move = generateRandomPossibleMove(ghostIndex, board);
			printf("Move: x=%d, y=%d\n", move.x, move.y);
			moveRespectingRules(move, ghostIndex, board);
			// zatrzymalem sie na etapie przekazywania informacji o stanie
			// gry. Mam do rozwiazania nastepujace problemy:
			// jak prezentowac w grze moment "zbijania" jednej figury przez druga?
			// jak łaczyc gre z interfejsem graficznym?
		}
	printTheBoard(board);
	}		
}
