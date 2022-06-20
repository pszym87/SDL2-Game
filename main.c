#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"

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

int main(){
	
	int board[BSIZE_HEIGHT][BSIZE_WIDTH] = {
	{ -1 ,  1 ,  10, -1 , 1 , 1 , 1 , 1 }, 
	{  1 , -1 ,  1 , -1 , 1 , -1,-1 , 1 }, 
	{  4 ,  1 ,  1 ,  1 ,-1 , 1 , 1 , 1 },
	{  0 , -1 , -1 , -1 , 1 , -1, -1, 1 }
	};

	index_t marioIndex = getAnIndexPositionOf(10,board);
	index_t ghostIndex = getAnIndexPositionOf(4,board);
	printIndexPosition(marioIndex);
	printIndexPosition(ghostIndex);
	printTheBoard(board);
	onePlayerPlay(&marioIndex, &ghostIndex, board);
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
